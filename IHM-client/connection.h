#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMainWindow>
#include <QCoreApplication>
//#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Dialog;
}
QT_END_NAMESPACE

class Connection: public QMainWindow {
    Q_OBJECT
public:
    explicit Connection(QWidget *parent);

    ~Connection() override;

    void connect();
private:
//    QSqlDatabase db =
    Ui::Dialog *ui;
};

#endif // CONNECTION_H
