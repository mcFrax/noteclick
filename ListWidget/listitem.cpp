#include "listitem.h"
#include <QMouseEvent>
#include <QDrag>
#include <QDataStream>
#include <QMimeData>
#include <QPixmap>
#include <QPainter>

#include <QMessageBox>

using namespace StructureView;


ListItem::ListItem(QWidget *parent) :
    QWidget(parent)
{

}

void ListItem::setDraggableType(QString type)
{
    draggableType = type;
}

void ListItem::mousePressEvent(QMouseEvent *event)
{

    QPixmap pixmap(this->size());
    this->render(&pixmap);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << (qint64)this;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData(draggableType, itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();


    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        this->close();
    } else {
        this->show();
    }
}



void ListItem::renamed(QString s)
{
    emit rename(this, s);
}

