#include "listname.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>

ListName::ListName(QWidget *parent) :
    QLabel(parent)
{
}

ListName::ListName(QString name, QWidget *parent) :
    QLabel(name, parent)
{
}


void ListName::mouseDoubleClickEvent(QMouseEvent *)
{
    bool ok;
    QString text = QInputDialog::getText(0, tr("Change name"),
                                         tr("Name:"), QLineEdit::Normal,
                                         this->text(), &ok);
    if (ok && !text.isEmpty())
    {
        //this->setText(text);
        emit rename(text);

    }
}
