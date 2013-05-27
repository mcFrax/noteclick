#ifndef LISTITEM_H
#define LISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

namespace StructureView
{

class ListItem : public QWidget
{
    Q_OBJECT
public:
    explicit ListItem(QWidget *parent = 0);
    virtual void setText(QString name) = 0;

signals:
    void removed(ListItem* id);
    void rename(ListItem* l, QString s);

public slots:

    virtual void renamed(QString s);
protected:

    QString draggableType;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void setDraggableType(QString type);

};

}
#endif // LISTITEM_H
