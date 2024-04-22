#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
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

    void moveCam(int value);

    void createCube();

    void createSphere();

    void createCylinder();

    void openTongs();

    void closeTongs();

    void moveAxePosOne();

    void moveAxeNegOne();

    void moveAxePosTwo();

    void moveAxeNegTwo();

    void moveAxePosThree();

    void moveAxeNegThree();

    void stopMove();


private:
    Ui::MainWindow *ui;
    GrpcServiceClient *m_grpcClient = nullptr;
    QPushButton *m_button_up;
    QPushButton *m_button_down;
    QPushButton *m_button_right;
    QPushButton *m_button_left;
    QSlider *m_slider;
    QLabel *m_labelValue;
    QPushButton *m_button_open;
    QPushButton *m_button_close;
    QPushButton *m_button_x1;
    QPushButton *m_button_x2;
    QPushButton *m_button_x1_2;
    QPushButton *m_button_x2_2;
    QPushButton *m_button_x1_3;
    QPushButton *m_button_x2_3;
    QPushButton *m_button_cube;
    QPushButton *m_button_sphere;

    QPushButton *m_button_cylinder;

};

#endif // MAINWINDOW_H
