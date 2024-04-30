#include "connection.h"
#include "ui_connection.h"
#include "mainwindow.h"
#include "register.h"
#include <sqlite3.h>
#include <QMessageBox>

Connection::Connection(const char *dbName, QWidget *parent) :
        QMainWindow(parent), ui(new Ui::Connection), m_db(nullptr), m_dbName(dbName) {
    ui->setupUi(this);
    connect(ui->pb_connect, &QPushButton::clicked, this, &Connection::on_pb_connect_clicked);
    connect(ui->pb_signup, &QPushButton::clicked, [this]() {
        if (m_register == nullptr) {
            m_register = new Register("db", this);
        }
        this->close();
        this->hide();
        m_register->show();
    });
}

Connection::~Connection() {
    delete m_mainWindow;
    delete ui;
    close();
}

bool Connection::open() {
    return sqlite3_open(m_dbName.toStdString().c_str(), &m_db) == SQLITE_OK;
}

void Connection::close() {
    if (m_db)
        sqlite3_close(m_db);
}

bool Connection::isOpen() const {
    return m_db != nullptr;
}

bool Connection::executeQuery(const QString& queryString, std::function<void(bool, const QStringList&)> callback) {
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

    callback(true, userData);
    return true;
}

void Connection::on_pb_connect_clicked() {
    QString username = ui->le_login->text();
    QString password = ui->le_password->text();

    if (this->open()) {
        QString queryString = QString("SELECT * FROM users WHERE username='%1' AND password='%2'")
                .arg(username).arg(password);
        this->executeQuery(queryString, [this](bool success, const QStringList& userData) {
            if (success) {
                if (!userData.isEmpty()) {
                    // Utilisateur trouvé dans la base de données, récupérez les données de l'utilisateur
                    QString username = userData.value(0);
                    QString email = userData.value(1);
                    // Faites quelque chose avec les données de l'utilisateur
                    qDebug() << "Utilisateur trouvé:" << username << email;
                    if (m_mainWindow == nullptr) {
                        m_mainWindow = new MainWindow();
                        this->close();
                        this->hide();
                        m_mainWindow->show();
                    }
                    return;
                } else {
                    // Utilisateur non trouvé dans la base de données
                    qDebug() << "Utilisateur non trouvé";
                }
            } else {
                // La requête a échoué
                QMessageBox::warning(this, "Error", "Query execution failed!");
            }
        });
    } else {
        // Impossible d'ouvrir la connexion à la base de données
        QMessageBox::critical(this, "Error", "Database connection failed!");
    }
}
