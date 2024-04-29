#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <memory>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_grpcClient = new GrpcServiceClient(grpc::CreateChannel("10.33.73.161:50051", grpc::InsecureChannelCredentials()));

    m_button_up = ui->Top;
    m_button_down = ui->Bottom;
    m_button_left = ui->Left;
    m_button_right = ui->Right;

    m_slider = ui->CamSlider;
    m_labelValue = ui->SliderValue;

    m_button_open = ui->Open;
    m_button_close = ui->Close;
    m_button_x1 = ui->X1;
    m_button_x2 = ui->x2;
    m_button_x1_2 = ui->X1_2;
    m_button_x2_2 = ui->x2_2;
    m_button_x1_3 = ui->X1_3;
    m_button_x2_3 = ui->x2_3;
    m_button_cube = ui->Cube;
    m_button_sphere = ui->Sphere;
    m_button_cylinder = ui->Cylindre;


    connect(m_button_up, &QPushButton::pressed, this, &MainWindow::moveUp);
    connect(m_button_up, &QPushButton::released, this, &MainWindow::stopMove);
    connect(m_button_down, &QPushButton::pressed, this, &MainWindow::moveDown);
    connect(m_button_down, &QPushButton::released, this, &MainWindow::stopMove);
    connect(m_button_left, &QPushButton::pressed, this, &MainWindow::moveLeft);
    connect(m_button_left, &QPushButton::released, this, &MainWindow::stopMove);
    connect(m_button_right, &QPushButton::pressed, this, &MainWindow::moveRight);
    connect(m_button_right, &QPushButton::released, this, &MainWindow::stopMove);
    connect(m_slider, &QSlider::valueChanged, this, &MainWindow::moveCam);
    connect(m_button_cube, &QPushButton::clicked, this, &MainWindow::createCube);
    connect(m_button_sphere, &QPushButton::clicked, this, &MainWindow::createSphere);
    connect(m_button_cylinder, &QPushButton::clicked, this, &MainWindow::createCylinder);
    connect(m_button_open, &QPushButton::clicked, this, &MainWindow::openTongs);
    connect(m_button_close, &QPushButton::clicked, this, &MainWindow::closeTongs);
    connect(m_button_x1, &QPushButton::pressed, this, &MainWindow::moveAxeNegOne);
    connect(m_button_x2, &QPushButton::pressed, this, &MainWindow::moveAxePosOne);
    connect(m_button_x1, &QPushButton::released, this, &MainWindow::stopAxeOne);
    connect(m_button_x2, &QPushButton::released, this, &MainWindow::stopAxeOne);
    connect(m_button_x1_2, &QPushButton::pressed, this, &MainWindow::moveAxeNegTwo);
    connect(m_button_x2_2, &QPushButton::pressed, this, &MainWindow::moveAxePosTwo);
    connect(m_button_x1_2, &QPushButton::released, this, &MainWindow::stopAxeTwo);
    connect(m_button_x2_2, &QPushButton::released, this, &MainWindow::stopAxeTwo);
    connect(m_button_x1_3, &QPushButton::pressed, this, &MainWindow::moveAxeNegThree);
    connect(m_button_x2_3, &QPushButton::pressed, this, &MainWindow::moveAxePosThree);
    connect(m_button_x1_3, &QPushButton::released, this, &MainWindow::stopAxeThree);
    connect(m_button_x2_3, &QPushButton::released, this, &MainWindow::stopAxeThree);
}

MainWindow::~MainWindow() {
    delete m_grpcClient;
    delete ui;
}


void MainWindow::moveUp() {
    qDebug("Déplacement vers l'avant");
    m_grpcClient->MoveBot("av");
}

void MainWindow::moveDown() {
    qDebug("Déplacement vers l'arrière");
    m_grpcClient->MoveBot("ar");
}

void MainWindow::moveLeft() {
    qDebug("Rotation vers la gauche");
    m_grpcClient->RotaBot("g");
}

void MainWindow::moveRight() {
    m_grpcClient->RotaBot("d");
    qDebug("Rotation vers la droite");
}

void MainWindow::stopMove() {
    qDebug("Arrêt du déplacement");
    m_grpcClient->MoveBot("stop");
    m_grpcClient->RotaBot("stop");
}

void MainWindow::moveCam(int value) {
    m_grpcClient->MoveCam(value);
    m_labelValue->setText(QString::number(value));
    qDebug("Déplacement de la caméra");
}

void MainWindow::createCube() {
    m_grpcClient->InstanceObject("cube");
    qDebug() << "Création d'un cube";
}

void MainWindow::createSphere() {
    m_grpcClient->InstanceObject("sphere");
    qDebug() << "Création d'une sphère";
}

void MainWindow::createCylinder() {
    m_grpcClient->InstanceObject("cylindre");
    qDebug() << "Création d'un cylindre";
}

void MainWindow::openTongs() {
    m_grpcClient->TongsManageOpening(true);
    qDebug() << "Ouverture des pinces";
}

void MainWindow::closeTongs() {
    m_grpcClient->TongsManageOpening(false);
    qDebug() << "Fermeture des pinces";
}

void MainWindow::moveAxePosOne() {
    m_grpcClient->TongsManageMove("axe1", 1);
    qDebug() << "Déplacement de l'axe 1 vers la position 1";
}

void MainWindow::moveAxeNegOne() {
    m_grpcClient->TongsManageMove("axe1", -1);
    qDebug() << "Déplacement de l'axe 1 vers la position -1";
}

void MainWindow::moveAxePosTwo() {
    m_grpcClient->TongsManageMove("axe2", 1);
    qDebug() << "Déplacement de l'axe 2 vers la position 1";
}

void MainWindow::moveAxeNegTwo() {
    m_grpcClient->TongsManageMove("axe2", -1);
    qDebug() << "Déplacement de l'axe 2 vers la position -1";
}

void MainWindow::moveAxePosThree() {
    m_grpcClient->TongsManageMove("pince", 1);
    qDebug() << "Déplacement de l'axe 3 vers la position 1";
}

void MainWindow::moveAxeNegThree() {
    m_grpcClient->TongsManageMove("pince", -1);
    qDebug() << "Déplacement de l'axe 3 vers la position -1";
}

void MainWindow::stopAxeOne() {
    m_grpcClient->TongsManageMove("axe1", 0);
    qDebug() << "Arrêt de l'axe 1";
}

void MainWindow::stopAxeTwo() {
    m_grpcClient->TongsManageMove("axe2", 0);
    qDebug() << "Arrêt de l'axe 2";
}

void MainWindow::stopAxeThree() {
    m_grpcClient->TongsManageMove("pince", 0);
    qDebug() << "Arrêt de l'axe 3";
}