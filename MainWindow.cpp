#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QtGlobal>

#include "SignalCommunication/UserAction.h"
#include "SystemImageInfo.h"
#include "SystemView/AddStaffState.h"
#include "SystemView/AddClefState.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupSceneStateTransitions();

    connect(&scene, SIGNAL(error(QString)), this, SLOT(handleError(QString)));
    connect(&scene, SIGNAL(warning(QString)), this, SLOT(handleWarning(QString)));
    connect(&scene, SIGNAL(notice(QString)), this, SLOT(handleNotice(QString)));

    connect(&score, SIGNAL(error(QString)), this, SLOT(handleError(QString)));
    connect(&score, SIGNAL(warning(QString)), this, SLOT(handleWarning(QString)));
    connect(&score, SIGNAL(notice(QString)), this, SLOT(handleNotice(QString)));

    connect(&scene, SIGNAL(userAction(UserAction)), &score, SLOT(userAction(UserAction)));
    connect(&score, SIGNAL(changed(ScoreChange)), &scene, SLOT(scoreChange(ScoreChange)));

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

void MainWindow::handleNotice(QString messageText)
{
    const QByteArray& array = messageText.toLocal8Bit();
    qDebug("%s\n", array.data());
}


void MainWindow::on_actionLoad_Image_triggered()
{
    QString fn = QFileDialog::getOpenFileName(this, tr("Otworz obraz..."));
    if (fn.isNull()) return;

    score.userAction(
                UserAction(
                    UserAction::CreateSystemImage,
                    vsa(scene.id(), SystemImageInfo(fn))
                    )
                );
    #warning to juz nie dziala, a nic nowego nie ma! scene.addSystemImageItem(fn);
}

void MainWindow::setupSceneStateTransitions()
{
    scene.states().editSystem->addTransition(
                ui->actionLoad_Image, SIGNAL(triggered()),
                scene.states().normalCursor);

    scene.states().editSystem->addTransition(
                ui->toolButton, SIGNAL(clicked()),
                scene.states().normalCursor);
    scene.states().editSystem->addTransition(
                ui->toolButton_2, SIGNAL(clicked()),
                scene.states().addStaff);
    scene.states().editSystem->addTransition(
                ui->toolButton_3, SIGNAL(clicked()),
                scene.states().addClef);
}

