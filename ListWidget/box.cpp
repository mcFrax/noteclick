#include "box.h"
#include <QLabel>
#include <QStyleOption>
#include <QPainter>

#include "innerlist.h"

Box::Box(QWidget *parent) :
    QWidget(parent)
{
}

Box::Box(QString name, QWidget *parent) :
    QWidget(parent)
{
    // creating contents objects
    addButton = new QPushButton(name);

    // setting layout
    layout = new QHBoxLayout;
    listLayout = new QVBoxLayout;
    outerListLayout = new QVBoxLayout;

    outerListLayout->addLayout(listLayout);
    outerListLayout->addWidget(addButton);

    //layout->addSpacerItem(new QSpacerItem(25,0));
    layout->addLayout(outerListLayout);
    layout->setMargin(0);
    setMyStyle();
    setLayout(layout);

    // connecting button
    connect(addButton, SIGNAL(clicked()), parent, SLOT(slotAddElement()));
}

void Box::setMyStyle()
{
    setObjectName("Box");
    setStyleSheet(
        "Box {"
        "border: 0px;"
        "background-color: white;}"
        );

}

void Box::addElement(QWidget *w)
{
    listLayout->addWidget(w);
}


void Box::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Box::addWidget(QWidget *w)
{
    listLayout->addWidget(w);
}
