#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <memory>
#include <QPushButton>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_grpcClient = new GrpcServiceClient(grpc::CreateChannel("10.33.73.161:50051", grpc::InsecureChannelCredentials()));

    auto *button_up = ui->Top;
    auto *button_down = ui->Bottom;
    auto *button_left = ui->Left;
    auto *button_right = ui->Right;

    QVBoxLayout *layout = new QVBoxLayout(this);

    auto *slider = ui->CamSlider;

    layout->addWidget(slider);

    connect(button_up, &QPushButton::clicked, this, &MainWindow::moveUp);
    connect(button_down, &QPushButton::clicked, this, &MainWindow::moveDown);
    connect(button_left, &QPushButton::clicked, this, &MainWindow::moveLeft);
    connect(button_right, &QPushButton::clicked, this, &MainWindow::moveRight);
    connect(slider, &QSlider::valueChanged, this, &MainWindow::moveCam);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::moveUp() {
    qDebug("Déplacement vers le haut");
    m_grpcClient->MoveTrans("up", 1);
}

void MainWindow::moveDown() {
    qDebug("Déplacement vers le bas");
    m_grpcClient->MoveTrans("down", 1);
}

void MainWindow::moveLeft() {
    qDebug("Déplacement vers la gauche");
    m_grpcClient->MoveTrans("left", 1);
}

void MainWindow::moveRight() {
    m_grpcClient->MoveTrans("right", 1);
    qDebug("Déplacement vers la droite");
}

void MainWindow::moveCam(int value) {
    m_grpcClient->MoveCam(value);
    qDebug("Déplacement de la caméra");
}