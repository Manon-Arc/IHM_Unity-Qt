//
// Created by ahliko on 12/05/24.
//

#ifndef IHM_PROJECTS_H
#define IHM_PROJECTS_H

#include <QDialog>
#include <sqlite3.h>
#include "mainwindow.h"
#include "db.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Projects; }
QT_END_NAMESPACE

class Projects : public QDialog {
Q_OBJECT

public:
    explicit Projects(Db *db, QString username, QWidget *parent = nullptr);

    ~Projects() override;

public slots:

    void createProject(const QString &name);

private slots:

    void on_pushButton_validate_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_new_clicked();

    void onProjectSelected();

private:

    void printProjects();

    void deleteProject(const QString &name);

    void openProject(const QString &name);

    int getIdProject(const QString &name);

    Db *m_db;
    Ui::Projects *ui;
    MainWindow *m_mainWindow = nullptr;
    QString m_projectName_selected;
    QString m_username;
};


#endif //IHM_PROJECTS_H
