//
// Created by ahliko on 12/05/24.
//

#ifndef IHM_CREATEPROJECT_H
#define IHM_CREATEPROJECT_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class CreateProject; }
QT_END_NAMESPACE

class CreateProject : public QDialog {
Q_OBJECT

public:
    explicit CreateProject(QWidget *parent = nullptr);

    ~CreateProject() override;

signals:

    void projectCreated(const QString &name);

private slots:

    void on_createButton_clicked();
private:
    Ui::CreateProject *ui;
};


#endif //IHM_CREATEPROJECT_H
