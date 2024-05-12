//
// Created by ahliko on 12/05/24.
//

#ifndef IHM_DB_H
#define IHM_DB_H


#include <QString>

class Db {
public:
    explicit Db(const char *dbName);

    ~Db();

    bool openDb();

    void close();

    bool isOpen() const;

    bool executeQuery(const QString &queryString, std::function<bool(bool, const QStringList &)> callback);

    int getProjectId(const QString &name);

    int getUserId(const QString &name);

private:
    sqlite3* m_db;
    QString m_dbName;
};


#endif //IHM_DB_H
