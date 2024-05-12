//
// Created by ahliko on 12/05/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CreateProject.h" resolved

#include "createproject.h"
#include "ui_createproject.h"


CreateProject::CreateProject(QWidget *parent) :
        QDialog(parent), ui(new Ui::CreateProject) {
    ui->setupUi(this);
}

CreateProject::~CreateProject() {
    delete ui;
}

void CreateProject::on_createButton_clicked() {
    emit projectCreated(ui->lineEdit_Name->text());
    close();
    hide();
}
