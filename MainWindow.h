#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "SystemView/SystemScene.h"
#include "Model/ScoreModel.h"

namespace Ui {
class MainWindow;
}

class QString;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleError(QString messageText);
    void handleWarning(QString messageText);
    void handleNotice(QString messageText);

private slots:
    void on_actionLoad_Image_triggered();

private:
    Ui::MainWindow *ui;
    SystemView::SystemScene scene;
    Model::ScoreModel score;
    void setupSceneStateTransitions();
};

#endif // MAINWINDOW_H
