//
// Created by ahliko on 29/04/24.
//

#ifndef IHM_REGISTER_H
#define IHM_REGISTER_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class Register; }
QT_END_NAMESPACE

class Register : public QDialog {
Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);

    ~Register() override;

private:
    Ui::Register *ui;
};


#endif //IHM_REGISTER_H
