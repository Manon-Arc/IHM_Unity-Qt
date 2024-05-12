//
// Created by ahliko on 12/05/24.
//

#include <sqlite3.h>
#include <QList>
#include "db.h"
#include <QDebug>

Db::Db(const char *dbName) : m_dbName(dbName) {
    openDb();
}

Db::~Db() {
    close();
}

bool Db::executeQuery(const QString &queryString, std::function<bool(bool, const QStringList &)> callback) {
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

bool Db::openDb() {
    return sqlite3_open(m_dbName.toStdString().c_str(), &m_db) == SQLITE_OK;
}

void Db::close() {
    if (m_db)
        sqlite3_close(m_db);
}

bool Db::isOpen() const {
    return m_db != nullptr;
}

int Db::getProjectId(const QString &name) {
    int res = -1;
    if (openDb()) {
        QString queryString = QString("SELECT Id FROM projects WHERE name='%1'")
                .arg(name);

        executeQuery(queryString, [&res](bool success, const QStringList& userData) {
            if (success) {
                if (!userData.isEmpty()) {
                    res = userData.value(0).toInt();
                    return true;
                }
            }
            return false;
        });
    }
    return res;
}

int Db::getUserId(const QString &name) {
    int res = -1;
    if (openDb()) {
        QString queryString = QString("SELECT Id FROM users WHERE username='%1'")
                .arg(name);

        executeQuery(queryString, [&res](bool success, const QStringList& userData) {
            if (success) {
                if (!userData.isEmpty()) {
                    res = userData.value(0).toInt();
                    return true;
                }
            }
            return false;
        });
    }
    return res;
}
