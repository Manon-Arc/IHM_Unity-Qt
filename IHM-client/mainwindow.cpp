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
    m_button_cube = ui->Cube;
    m_button_sphere = ui->Sphere;
    m_button_cylinder = ui->Cylindre;


    connect(m_button_up, &QPushButton::clicked, this, &MainWindow::moveUp);
    connect(m_button_down, &QPushButton::clicked, this, &MainWindow::moveDown);
    connect(m_button_left, &QPushButton::clicked, this, &MainWindow::moveLeft);
    connect(m_button_right, &QPushButton::clicked, this, &MainWindow::moveRight);
    connect(m_slider, &QSlider::valueChanged, this, &MainWindow::moveCam);
    connect(m_button_cube, &QPushButton::clicked, this, &MainWindow::createCube);
    connect(m_button_sphere, &QPushButton::clicked, this, &MainWindow::createSphere);
    connect(m_button_cylinder, &QPushButton::clicked, this, &MainWindow::createCylinder);
    connect(m_button_open, &QPushButton::clicked, this, &MainWindow::openTongs);
    connect(m_button_close, &QPushButton::clicked, this, &MainWindow::closeTongs);
}

MainWindow::~MainWindow() {
    delete m_grpcClient;
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
    m_grpcClient->InstanceObject("cylinder");
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
