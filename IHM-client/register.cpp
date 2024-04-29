//
// Created by ahliko on 29/04/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Register.h" resolved

#include "register.h"
#include "ui_Register.h"


Register::Register(QWidget *parent) :
        QDialog(parent), ui(new Ui::Register) {
    ui->setupUi(this);
}

Register::~Register() {
    delete ui;
}
