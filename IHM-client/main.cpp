#include "mainwindow.h"
#include "connection.h"
#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Connection w = Connection("db", nullptr);
    w.show();
    return a.exec();
}

//#include <qdebug.h>
//#include "hash.h"
//
//int main(int argc, char *argv[]) {
//    qDebug() << "here";
//    Hash hash;
//    QString mdp = hash.hashPassword("password");
//    qDebug() << mdp;
//    qDebug() << hash.verifyPassword(mdp, "password");
//    qDebug() << hash.verifyPassword("$argon2id$v=19$m=65536,t=2,p=1$E9QpOsXKoFyJbkHFskv3qg$zIsSrD7OSW3E0cwQvBInI3knESdH6iVg0AZ7dWjA9bw", "password");
//}
