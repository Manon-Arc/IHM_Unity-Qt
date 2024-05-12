#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMainWindow>
#include <QCoreApplication>
#include <sqlite3.h>
#include "mainwindow.h"
#include "register.h"
#include "hash.h"
#include "projects.h"
#include "db.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Connection;
}
QT_END_NAMESPACE

class Connection : public QMainWindow {
Q_OBJECT

public:
    explicit Connection(Db *db, QWidget *parent);

    ~Connection() override;

private slots:
    void on_pb_connect_clicked();
private:
    Projects *m_projectWindow = nullptr;
    Db* m_db;
    Ui::Connection *ui;
    Register *m_register = nullptr;
    Hash *m_hash;
};

#endif // CONNECTION_H
