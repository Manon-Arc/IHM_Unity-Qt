//
// Created by ahliko on 29/04/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Register.h" resolved

#include <QMessageBox>
#include "register.h"
#include "ui_register.h"


Register::Register(Db *db, QWidget *parent) :
        QDialog(parent), ui(new Ui::Register), m_db(db), m_parent(parent) {
    ui->setupUi(this);
    m_hash = new Hash();
        connect(ui->pb_validate, &QPushButton::clicked, this, &Register::on_pb_validate_clicked);
        connect(ui->pb_signin, &QPushButton::clicked, this, &Register::on_pb_signin_clicked);
    connect(this, &QDialog::finished, [this](int result) {
        if (result == QDialog::Rejected) {
            delete this;
        }
    });
}

Register::~Register() {
    qDebug() << "Register::~Register()";
    delete ui;
    QApplication::quit();
}

void Register::on_pb_signin_clicked() {
    if (m_parent != nullptr) {
        this->hide();
        m_parent->show();
    }
}

void Register::on_pb_validate_clicked() {
    if (ui->password1->text() != ui->password2->text()) {
        QMessageBox::warning(this, "Error", "Passwords do not match!");
        return;
    }
    QString firstname = ui->firstname->text();
    QString name = ui->name->text();
    QString username = ui->username->text();
    QString password = ui->password1->text();

    if (m_db->openDb()) {
        QString queryString = QString("SELECT COUNT(*) FROM users WHERE username = '%1'")
                .arg(username);
        if (!m_db->executeQuery(queryString, [this](bool success, const QStringList& userData) {
            if (success) {
                if (!userData.isEmpty()) {
                    // Utilisateur trouvé dans la base de données, récupérez les données de l'utilisateur
                    int nb = userData.value(0).toInt();
                    // Faites quelque chose avec les données de l'utilisateur
                    if (nb > 0) {
                        QMessageBox::warning(this, "Error", "User already exists!");
                        return  false;
                    } else {
                        return true;
                    }
                } else {
                    // Utilisateur non trouvé dans la base de données
                    qDebug() << "Utilisateur non trouvé";
                    return false;

                }
            } else {
                // La requête a échoué
                QMessageBox::warning(this, "Error", "Query execution failed!");
                return false;
            }
        })) return;

        QString hashPassword = m_hash->hashPassword(password.toStdString().c_str());

        queryString = QString("INSERT INTO users (firstname, name, username, password) VALUES ('%1', '%2', '%3', '%4')")
                .arg(firstname).arg(name).arg(username).arg(hashPassword);
        m_db->executeQuery(queryString, [this, &username](bool success, const QStringList& userData) {
            if (success) {
                if (m_projectWindow == nullptr) {
                    m_projectWindow = new Projects(m_db, username, this);
                }
                this->hide();
                if (m_parent != nullptr) {
                    m_parent->close();
                    m_parent->hide();
                }
                m_projectWindow->show();
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