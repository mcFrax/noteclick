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

SystemImageDialog::exec()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open File"),"/path/to/file/",tr("pdf files (*.pdf)"));
    ui->listWidget->addItems(fileNames);
    this->show();
}
