#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include "innerlist.h"
#include <QScrollArea>

namespace StructureView
{

class ListWidget : public InnerList
{
    Q_OBJECT
public:
    explicit ListWidget(QString name, QWidget *parent = 0);

signals:

public slots:
    

protected:
    QScrollArea *scrollArea;
    QVBoxLayout *scrollLayout;

};

}

#endif // LISTWIDGET_H
