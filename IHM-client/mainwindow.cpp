#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <memory>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_grpcClient = new MovementClient(grpc::CreateChannel("10.33.73.161:50051", grpc::InsecureChannelCredentials()));

    auto *button_up = ui->pushButton_4;
    auto *button_down = ui->pushButton_2;
    auto *button_left = ui->pushButton_3;
    auto *button_right = ui->pushButton;

    connect(button_up, &QPushButton::clicked, this, &MainWindow::moveUp);
    connect(button_down, &QPushButton::clicked, this, &MainWindow::moveDown);
    connect(button_left, &QPushButton::clicked, this, &MainWindow::moveLeft);
    connect(button_right, &QPushButton::clicked, this, &MainWindow::moveRight);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::moveUp() {
    qDebug("Déplacement vers le haut");
    m_grpcClient->Move("up", 1);
}

void MainWindow::moveDown() {
    qDebug("Déplacement vers le bas");
    m_grpcClient->Move("down", 1);
}

void MainWindow::moveLeft() {
    qDebug("Déplacement vers la gauche");
    m_grpcClient->Move("left", 1);
}

void MainWindow::moveRight() {
    m_grpcClient->Move("right", 1);
    qDebug("Déplacement vers la droite");
}

void MainWindow::jump() {
    m_grpcClient->Move("jump", 1);
    qDebug("Saut");
}
