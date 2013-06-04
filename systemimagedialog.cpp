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
    if (fileName!=NULL)
        this->show();
}

void SystemImageDialog::on_resizer_valueChanged(int value)
{
    this->sizeScale=value;
}
