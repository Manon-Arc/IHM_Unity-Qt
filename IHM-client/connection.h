#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMainWindow>
#include <QCoreApplication>
#include <sqlite3.h>
#include "mainwindow.h"
#include "register.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Connection;
}
QT_END_NAMESPACE

class Connection : public QMainWindow {
Q_OBJECT

public:
    explicit Connection(const char *dbName, QWidget *parent);

    ~Connection() override;

    bool open();
    void close();
    bool isOpen() const;

    bool executeQuery(const QString& queryString, std::function<void(bool, const QStringList&)> callback);
    MainWindow *m_mainWindow = nullptr;
private slots:
    void on_pb_connect_clicked();
private:
    sqlite3* m_db;
    QString m_dbName;
    Ui::Connection *ui;
    Register *m_register = nullptr;
};

#endif // CONNECTION_H
