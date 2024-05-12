#include "connection.h"
#include "ui_connection.h"
#include "mainwindow.h"
#include "register.h"
#include <QMessageBox>

Connection::Connection(Db *db, QWidget *parent) :
        QMainWindow(parent), ui(new Ui::Connection), m_db(db) {
    ui->setupUi(this);
    m_hash = new Hash();
    connect(ui->pb_signup, &QPushButton::released, [this]() {
        if (m_register == nullptr) {
            m_register = new Register(m_db, this);
        }
        this->close();
        this->hide();
        m_register->show();
    });
}

Connection::~Connection() {
    delete ui;
    delete m_db;
    close();
    exit(0);
}

void Connection::on_pb_connect_clicked() {
    QString username = ui->le_login->text();

    if (m_db->openDb()) {
        QString queryString = QString("SELECT * FROM users WHERE username='%1'")
                .arg(username);

        m_db->executeQuery(queryString, [this](bool success, const QStringList& userData) {
            if (success) {
                if (!userData.isEmpty()) {
                    QString un = userData.value(1);
                    QString passwd = userData.value(2);
                    if (m_hash->verifyPassword(passwd, ui->le_password->text())) {
                        QMessageBox::warning(this, "Error", "Invalid password!");
                        return false;
                    }
                    if (m_projectWindow == nullptr) {
                        m_projectWindow = new Projects(m_db, un, this);
                        this->close();
                        this->hide();
                        m_projectWindow->show();
                        return true;
                    }
                    return false;
                } else {
                    // Utilisateur non trouvé dans la base de données
                    qDebug() << "Utilisateur non trouvé";
                }
            } else {
                // La requête a échoué
                QMessageBox::warning(this, "Error", "Query execution failed!");
            }
            return false;
        });
    } else {
        // Impossible d'ouvrir la connexion à la base de données
        QMessageBox::critical(this, "Error", "Database connection failed!");
    }
}
