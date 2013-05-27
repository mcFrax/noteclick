#include <QStyleOption>
#include <QPainter>
#include <QInputDialog>
#include <QLineEdit>
#include <QDir>
#include <QMessageBox>
#include <QSpacerItem>

#include "voicewidget.h"
#include "listname.h"

using namespace StructureView;


VoiceWidget::VoiceWidget(QString n, Score *sc, QWidget *parent) :
    ListItem(parent)
{

    score = sc;
    name = new ListName();
    name->setText(n);
    eraseButton = new EraseButton();
    checkBox = new QCheckBox();
    radioButton = new QRadioButton();

    layout = new QHBoxLayout;

    layout->addWidget(radioButton);
    layout->addWidget(name);
    layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
    layout->addWidget(checkBox);
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
    connect(radioButton, SIGNAL(clicked(bool)) , this, SLOT(selected()));
    connect(checkBox, SIGNAL(clicked()), this, SLOT(checked()));
    connect(this, SIGNAL(voiceChecked(void*,bool)), score, SLOT(voiceChecked(void*, bool)));
    connect(this, SIGNAL(voiceSelected(void*, bool)), score, SLOT(voiceSelected(void*, bool)));
    connect(this, SIGNAL(removed(ListItem*)), score, SLOT(elementRemoved(ListItem*)));

}

void VoiceWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void VoiceWidget::mouseDoubleClickEvent(QMouseEvent *)
{
    bool ok;

    QWidget *ptr = (QWidget*)this;
    while (ptr != ptr->parent() && !ptr->isWindow())
        ptr = (QWidget*)ptr->parent();

    QString text = QInputDialog::getText(ptr, tr("Change name"),
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


void VoiceWidget::selected()
{
    emit voiceSelected((void*)this, radioButton->isChecked());
}

void VoiceWidget::checked()
{
    emit voiceChecked((void*)this, checkBox->isChecked());
}

void VoiceWidget::setSelected(bool s)
{
    radioButton->setChecked(s);
}

// TODO to jakoś brzydko wylgąda...
void VoiceWidget::erase()
{
    emit removed(this);
}

VoiceWidget::~VoiceWidget()
{
    score->voiceSelected(this, false);
}
