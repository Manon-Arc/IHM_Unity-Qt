#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <memory>



MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    qDebug("test");
    ui->setupUi(this);
    m_grpcClient = new MovementClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
//    m_grpcClient->Move("up", 1);
}

MainWindow::~MainWindow() {
    delete ui;
}
