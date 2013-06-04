#include "systemimagedialog.h"
#include "ui_systemimagedialog.h"

SystemImageDialog::SystemImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemImageDialog)
{
    ui->setupUi(this);
}

SystemImageDialog::~SystemImageDialog()
{
    delete ui;
}

int SystemImageDialog::exec()
{
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/", tr("pdf files (*.pdf)"));
    this->fileName = fileName;
    pic = SystemImageInfo(fileName,transformation,1,frame);
    if (fileName!=NULL)
        this->show();
}

void SystemImageDialog::on_resizer_valueChanged(int value)
{
    int maxVal=255;
    transformation.scale(value/maxVal,value/maxVal);
    //ramka.pixmap= SystemImageInfo(fileName,transformation,page,frame).pixmap();
    //@up nie wiem jak sie odwolac do tego graphicsview w dialogu

}


void SystemImageDialog::on_spinBox_valueChanged(int page)
{
    this->page=page;
    SystemImageInfo(fileName,transformation,page,frame);
    //ramka.pixmap= pic.pixmap();
}

void SystemImageDialog::on_dial_valueChanged(int value)
{
    transformation.rotate(value);
    //ramka.pixmap= SystemImageInfo(fileName,transformation,page,frame).pixmap();
}

