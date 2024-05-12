//
// Created by ahliko on 29/04/24.
//

#ifndef IHM_REGISTER_H
#define IHM_REGISTER_H

#include <QMainWindow>
#include <QCoreApplication>
#include <sqlite3.h>
#include "mainwindow.h"
#include "hash.h"
#include "projects.h"
#include "db.h"
#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class Register; }
QT_END_NAMESPACE

class Register : public QDialog {
Q_OBJECT

public:
    explicit Register(Db *db, QWidget *parent = nullptr);

    ~Register() override;

protected:
    void on_pb_validate_clicked();
    void on_pb_signin_clicked();

private:
    Ui::Register *ui;

    bool openDb();

    void close();

    bool isOpen() const;

    bool executeQuery(const QString &queryString, std::function<bool(bool, const QStringList &)> callback);

    MainWindow *m_mainWindow = nullptr;
    Db* m_db;
    QWidget *m_parent = nullptr;
    Hash *m_hash;
    Projects *m_projectWindow = nullptr;
};


#endif //IHM_REGISTER_H
