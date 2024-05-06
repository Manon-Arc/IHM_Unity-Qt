#include "connection.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Connection w = Connection("../db", nullptr);
    w.show();
    return a.exec();
}
