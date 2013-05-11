#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupSceneStateTransitions();

    ui->systemView->setScene(&scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_Image_triggered()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Otworz obraz..."));
    if (fn.isNull()) return;

    scene.addSystemImageItem(fn);
}

void MainWindow::setupSceneStateTransitions()
{
    scene.states().editSystem->addTransition(
                ui->toolButton, SIGNAL(clicked()),
                scene.states().normalCursor);
<<<<<<< HEAD
//    scene.states().editSystem->addTransition(
//                ui->toolButton_2, SIGNAL(clicked()),
//                scene.states().addStaff);
=======
    scene.states().editSystem->addTransition(
                ui->toolButton_2, SIGNAL(clicked()),
                scene.states().addStaff);
>>>>>>> 408d556... MainWindow setup1
}
