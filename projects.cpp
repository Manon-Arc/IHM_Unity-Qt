//
// Created by ahliko on 12/05/24.
//

#include <QMessageBox>
#include <QModelIndexList>
#include <QTableWidget>
#include "projects.h"
#include "ui_projects.h"
#include "createproject.h"


Projects::Projects(Db *db, QString username, QWidget *parent) :
        QDialog(parent), ui(new Ui::Projects), m_db(db), m_username(username) {
    ui->setupUi(this);
    connect(ui->tableWidget, &QTableWidget::itemSelectionChanged, this, &Projects::onProjectSelected);
    connect(this, &QDialog::finished, [this](int result) {
        if (result == QDialog::Rejected) {
            delete this;
        }
    });
    printProjects();
}

Projects::~Projects() {
    delete ui;
    close();
    QApplication::quit();
}

void Projects::on_pushButton_new_clicked() {
    CreateProject createProject;
    connect(&createProject, &CreateProject::projectCreated, this, &Projects::createProject);
    createProject.exec();
}

void Projects::on_pushButton_delete_clicked() {
    deleteProject(m_projectName_selected);
}

void Projects::on_pushButton_validate_clicked() {
    openProject(m_projectName_selected);
}

void Projects::createProject(const QString &name) {

    if (name == "") {
        QMessageBox::warning(this, "Error", "Please enter a name!");
        return;
    }

    if (m_db->openDb()) {
        QString queryString = QString("SELECT COUNT(*) FROM projects WHERE name = '%1'")
                .arg(name);
        if (!m_db->executeQuery(queryString, [this](bool success, const QStringList &projectData) {
            if (success) {
                if (!projectData.isEmpty()) {
                    int nb = projectData.value(0).toInt();
                    if (nb > 0) {
                        QMessageBox::warning(this, "Error", "Project already exists!");
                        return false;
                    }
                    return true;
                }
                return false;
            } else {
                // La requête a échoué
                QMessageBox::warning(this, "Error", "Query execution failed!");
                return false;
            }
        }))
            return;

        queryString = QString("INSERT INTO projects (name) VALUES ('%1')")
                .arg(name);
        if (!m_db->executeQuery(queryString, [this](bool success, const QStringList &projectData) {
            if (success) {
                return true;
            } else {
                // La requête a échoué
                QMessageBox::warning(this, "Error", "Query execution failed!");
                return false;
            }
        }))
            return;


        queryString = QString("INSERT INTO user_project (user, project) VALUES ('%1', '%2')")
                .arg(m_db->getUserId(m_username)).arg(m_db->getProjectId(name));
        m_db->executeQuery(queryString, [this](bool success, const QStringList &projectData) {
            if (success) {
                if (m_mainWindow == nullptr) {
                    m_mainWindow = new MainWindow();
                }
                this->hide();
                m_mainWindow->show();
                return true;
            } else {
                // La requête a échoué
                QMessageBox::warning(this, "Error", "Query execution failed!");
                return false;
            }
        });
    } else {
        // Impossible d'ouvrir la connexion à la base de données
        QMessageBox::critical(this, "Error", "Database connection failed!");
    }
}

void Projects::deleteProject(const QString &name) {
    int projectId = m_db->getProjectId(name);
    if (m_db->openDb()) {
        QString queryString = QString("DELETE FROM projects WHERE name = '%1'")
                .arg(name);
        if (!m_db->executeQuery(queryString, [this](bool success, const QStringList &projectData) {
            if (success) {
                return true;
            } else {
                QMessageBox::warning(this, "Error", "Query execution failed!");
                return false;
            }
        }))
            return;
        queryString = QString("DELETE FROM user_project WHERE project = '%1'")
                .arg(projectId);
        if (!m_db->executeQuery(queryString, [this](bool success, const QStringList &projectData) {
            if (success) {
                return true;
            } else {
                QMessageBox::warning(this, "Error", "Query execution failed!");
                return false;
            }
        }))
            return;
        else printProjects();
    }
}

void Projects::openProject(const QString &name) {
    if (m_db->openDb()) {
        QString queryString = QString("SELECT COUNT(*) FROM projects WHERE name = '%1'")
                .arg(name);
        if (!m_db->executeQuery(queryString, [this](bool success, const QStringList &projectData) {
            if (success) {
                if (!projectData.isEmpty()) {
                    int nb = projectData.value(0).toInt();
                    if (nb == 0) {
                        QMessageBox::warning(this, "Error", "Project not exist!");
                        return false;
                    }
                    if (m_mainWindow == nullptr) {
                        m_mainWindow = new MainWindow();
                    }
                    this->close();
                    this->hide();
                    m_mainWindow->show();
                    return true;
                }
                return false;
            } else {
                QMessageBox::warning(this, "Error", "Query execution failed!");
                return false;
            }
        }))
            return;
    }
}

void Projects::printProjects() {
    ui->tableWidget->clear();
    if (m_db->openDb()) {
        QString queryString = "SELECT name FROM projects";
        if (!m_db->executeQuery(queryString, [this](bool success, const QStringList &projectData) {
            if (success) {
                ui->tableWidget->clearContents();
                ui->tableWidget->setRowCount(projectData.size());
                ui->tableWidget->setColumnCount(1);

                int row = 0;
                for (const QString &name: projectData) {
                    auto *itemName = new QTableWidgetItem(name);
                    ui->tableWidget->setItem(row, 0, itemName);
                    ui->tableWidget->setColumnWidth(row, ui->tableWidget->width());
                    ui->tableWidget->itemAt(row, 0)->setTextAlignment(Qt::AlignCenter);
                    ++row;
                }

                ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
                return true;
            } else {
                QMessageBox::warning(this, "Error", "Query execution failed!");
                return false;
            }
        }))
            return;
    }
}

void Projects::onProjectSelected() {
    QModelIndexList selectedRows = ui->tableWidget->selectionModel()->selectedRows();
    if (!selectedRows.isEmpty()) {
        int row = selectedRows.first().row();
        m_projectName_selected = ui->tableWidget->item(row, 0)->text();
    }
}
