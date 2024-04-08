#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();

private:
    Ui::MainWindow *ui;
    GrpcServiceClient *m_grpcClient = nullptr;
};

#endif // MAINWINDOW_H
