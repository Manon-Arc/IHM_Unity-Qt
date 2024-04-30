//
// Created by ahliko on 29/04/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Register.h" resolved

#include <QMessageBox>
#include "register.h"
#include "ui_register.h"
#include "mainwindow.h"


Register::Register(const char *dbName, QWidget *parent) :
        QDialog(parent), ui(new Ui::Register), m_db(nullptr), m_dbName(dbName), m_parent(parent) {
    ui->setupUi(this);
    connect(ui->pb_validate, &QPushButton::clicked, this, &Register::on_pb_validate_clicked);
    connect(ui->pb_signin, &QPushButton::clicked, this, &Register::on_pb_signin_clicked);
}

Register::~Register() {
    delete ui;
}

void Register::on_pb_signin_clicked() {
    if (m_parent != nullptr) {
        this->close();
        this->hide();
        m_parent->show();
    }
}

bool Register::openDb() {
    return sqlite3_open(m_dbName.toStdString().c_str(), &m_db) == SQLITE_OK;
}

void Register::close() {
    if (m_db)
        sqlite3_close(m_db);
}

bool Register::isOpen() const {
    return m_db != nullptr;
}


bool Register::executeQuery(const QString& queryString, std::function<bool(bool, const QStringList&)> callback) {
    if (!isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    char* errMsg;
    QStringList userData;
    int result = sqlite3_exec(m_db, queryString.toStdString().c_str(),
                              [](void* userDataPtr, int argc, char** argv, char** /*colNames*/) -> int {
                                  QStringList* userData = reinterpret_cast<QStringList*>(userDataPtr);
                                  for (int i = 0; i < argc; ++i) {
                                      userData->append(argv[i]);
                                  }
                                  return 0;
                              },
                              &userData, &errMsg);

    if (result != SQLITE_OK) {
        qDebug() << "SQL error: " << errMsg;
        sqlite3_free(errMsg);
        return false;
    }

    return callback(true, userData);
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

    if (this->openDb()) {



        QString queryString = QString("SELECT COUNT(*) FROM users WHERE username = '%1'")
                .arg(username);
        if (!this->executeQuery(queryString, [this](bool success, const QStringList& userData) {
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


        queryString = QString("INSERT INTO users (firstname, name, username, password) VALUES ('%1', '%2', '%3', '%4')")
                .arg(firstname).arg(name).arg(username).arg(password);
        this->executeQuery(queryString, [this](bool success, const QStringList& userData) {
            if (success) {
                if (m_mainWindow == nullptr) {
                    m_mainWindow = new MainWindow();
                }
                this->close();
                this->hide();
                if (m_parent != nullptr) {
                    m_parent->close();
                    m_parent->hide();
                }
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