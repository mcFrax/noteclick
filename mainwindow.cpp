#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupSceneStateTransitions();

    connect(&scene, SIGNAL(error(QString)), this, SLOT(handleError(QString)));
    connect(&scene, SIGNAL(warning(QString)), this, SLOT(handleWarning(QString)));

    ui->systemView->setScene(&scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleError(QString messageText)
{
    QMessageBox::critical(this, tr("Błąd"), messageText);
}

void MainWindow::handleWarning(QString messageText)
{
    const QByteArray& array = messageText.toLocal8Bit();
    qWarning("%s\n", array.data());
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
    scene.states().editSystem->addTransition(
                ui->toolButton_2, SIGNAL(clicked()),
                scene.states().addStaff);
}

