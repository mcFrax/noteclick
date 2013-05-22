#include <QStyleOption>
#include <QPainter>
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>
#include <QMessageBox>

#include "voicewidget.h"
#include "listname.h"

VoiceWidget::VoiceWidget(QString n, Score *sc, QWidget *parent) :
    ListItem(parent)
{
    score = sc;
    name = new ListName();
    name->setText(n);
    eraseButton = new EraseButton();
    layout = new QHBoxLayout;
    layout->addWidget(name);
    layout->addWidget(eraseButton);

    setLayout(layout);

    setObjectName("VoiceWidget");
    setStyleSheet(
                "VoiceWidget {"
                "border: 1px solid black;"
                "border-radius: 4px;"
                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 2,"
                  "stop: 0 #B4F200, stop: 1 #000000);"
                "}"
        );

    setDraggableType("VoiceWidget");

    connect(eraseButton, SIGNAL(clicked()), this, SLOT(erase()));

    connect(this, SIGNAL(removed(ListItem*)), score, SLOT(elementRemoved(ListItem*)));

}

void VoiceWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    //QLabel::paintEvent(0);
}

void VoiceWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    bool ok;
    QString text = QInputDialog::getText(0, tr("Change name"),
                                         tr("Name:"), QLineEdit::Normal,
                                         name->text(), &ok);
    if (ok && !text.isEmpty())
        name->setText(text);

    emit rename(this, text);
}

void VoiceWidget::mouseReleaseEvent(QMouseEvent *)
{
    bool ok;
    QString text = QInputDialog::getText(0, tr("Change name"),
                                         tr("Name:"), QLineEdit::Normal,
                                         name->text(), &ok);
    emit clicked();
}

void VoiceWidget::setText(QString n)
{
    name->setText(n);
}


// TODO to jakoś brzydko wylgąda...
void VoiceWidget::erase()
{
    emit removed(this);
}
