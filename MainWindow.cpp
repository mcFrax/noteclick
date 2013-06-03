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
#include "SystemView/AddNoteState.h"

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

    connect((ui->VoiceList), SIGNAL(userAction(UserAction)), &score, SLOT(userAction(UserAction)));
    connect(&score, SIGNAL(changed(ScoreChange)), (ui->VoiceList), SLOT(scoreChange(ScoreChange)));

    connect((ui->VoiceList), SIGNAL(voiceCheckedSignal(IdType,bool)), &scene, SLOT(voiceVisible(IdType,bool)));
    connect((ui->VoiceList), SIGNAL(voiceSelectedSignal(IdType)), &scene, SLOT(selectVoice(IdType)));

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
}

void MainWindow::setupSceneStateTransitions()
{
    scene.states().editSystem->addTransition(
                ui->actionLoad_Image, SIGNAL(triggered()),
                scene.states().normalCursor);

    scene.states().editSystem->assignProperty(ui->toolButton, "down", false);
    scene.states().editSystem->assignProperty(ui->toolButton_2, "down", false);
    scene.states().editSystem->assignProperty(ui->toolButton_3, "down", false);
    scene.states().editSystem->assignProperty(ui->toolButton_4, "down", false);

    scene.states().editSystem->addTransition(
                ui->toolButton, SIGNAL(clicked()),
                scene.states().normalCursor);
    scene.states().normalCursor->assignProperty(ui->toolButton, "down", true);
    scene.states().editSystem->addTransition(
                ui->toolButton_2, SIGNAL(clicked()),
                scene.states().addStaff);
    scene.states().addStaff->assignProperty(ui->toolButton_2, "down", true);
    scene.states().editSystem->addTransition(
                ui->toolButton_3, SIGNAL(clicked()),
                scene.states().addClef);
    scene.states().addClef->assignProperty(ui->toolButton_3, "down", true);
    scene.states().editSystem->addTransition(
                ui->toolButton_4, SIGNAL(clicked()),
                scene.states().addNote);
    scene.states().addNote->assignProperty(ui->toolButton_4, "down", true);
}

