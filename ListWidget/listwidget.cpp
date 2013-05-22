#include "listwidget.h"


ListWidget::ListWidget(QString name, QWidget *parent) :
    InnerList(name, parent)
{
    layout->removeWidget(box);

    scrollLayout = new QVBoxLayout;
    scrollLayout->addWidget(box);
    scrollLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));
    //scrollLayout->setMargin(1);

    QWidget *tmp = new QWidget;

    tmp->setLayout(scrollLayout);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::BrightText);
    scrollArea->setWidget(tmp);
    scrollArea->setWidgetResizable(true);
    scrollLayout->setMargin(0);

    layout->addWidget(scrollArea);

    setFixedWidth(300);

}

