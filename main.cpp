#include "connection.h"
#include "db.h"
#include <QSettings>
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QSettings settings(".env", QSettings::IniFormat);
    Connection w = Connection(new Db(settings.value("DB_PATH").toString().toStdString().c_str()), nullptr);
    w.show();
    return a.exec();
}
