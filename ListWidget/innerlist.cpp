#include "innerlist.h"

#include <QStyleOption>
#include <QPainter>
#include <QInputDialog>
#include <QMouseEvent>
#include <QDrag>
#include <QDataStream>
#include <QMimeData>
#include <QPixmap>

//TMP
#include <QMessageBox>

#include "listitem.h"
#include "erasebutton.h"


InnerList::InnerList(QString name, QWidget *parent) :
    ListItem(parent)
{
    // creating content objects
    box = new Box("",this);
    setButtonText("Add element");
    layout = new QVBoxLayout;
    headerLayout = new QHBoxLayout;
    nameLabel = new ListName(name);
    plusButton = new QPushButton("-");
    eraseButton = new EraseButton();

    // settin content objects
    // TODO te zromiary zastapic jakas stałą
    plusButton->setFixedHeight(23);
    plusButton->setFixedWidth(23);


    // setting styles
    setMyStyle();

    // setting layouts
    //headerLayout->addWidget(plusButton);
    //headerLayout->addWidget(nameLabel);
    headerLayout->addWidget(nameLabel);
    headerLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Minimum));
    headerLayout->addWidget(eraseButton );

    layout->addLayout(headerLayout);
    layout->addWidget(box);
    layout->setMargin(1);
    setLayout(layout);

    // connecting buttons
    connect(plusButton, SIGNAL(clicked()), this, SLOT(toggle()));
    connect(eraseButton, SIGNAL(clicked()), this, SLOT(erase()));
    //connect(box->addButton, SIGNAL(clicked()), this, SLOT(addElement()));
    connect(nameLabel, SIGNAL(rename(QString)), this, SLOT(renamed(QString)));


    // setting some variables
    hidden = false;

    setAcceptDrops(true);

    // setting accepted drops
    acceptedDrops.insert("InnerList");

    // setting dragable type
    setDraggableType("InnerList");


}

void InnerList::setMyStyle()
{
    setObjectName("InnerList");
    setStyleSheet(
        "InnerList {"
        "border: 0px;"
        "background-color: white;"
        "border-top: 1px solid black;"
        "border-bottom: 1px solid black;}"
        );

}

void InnerList::setText(QString name)
{
    nameLabel->setText(name);
}

void InnerList::toggle()
{
    if (hidden)
    {
        box->show();
        plusButton->setText("-");
    }
    else
    {
        box->hide();
        plusButton->setText("+");
    }
    hidden = !hidden;
}


void InnerList::slotAddElement()
{
    box->addElement(defaultElement());
}

void InnerList::addElement(ListItem *element)
{
    box->addElement(element);
}

QWidget * InnerList::defaultElement()
{
    return new InnerList("Element");
}

void InnerList::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void InnerList::dragEnterEvent(QDragEnterEvent *event)
{
    foreach(QString str, acceptedDrops)
    {
        if (event->mimeData()->hasFormat(str)) {
            if (event->source() == this) {
                //event->setDropAction(Qt::MoveAction);
                //event->accept();
                event->ignore();
            } else {
                event->acceptProposedAction();

            }

            return;
        }
    }

    event->ignore();
}

void InnerList::dropEvent(QDropEvent *event)
{
    QObject *p = this;
    while(p != 0) {
        if (event->source() == p)
            return;
        p = p->parent();
    }

    foreach(QString str, acceptedDrops)
    {
        if (event->mimeData()->hasFormat(str)) {
            QByteArray itemData = event->mimeData()->data(str);
            QDataStream dataStream(&itemData, QIODevice::ReadOnly);

            QWidget *item;
            qint64 tmp;
            dataStream >> tmp;

            item = (QWidget *)tmp;

            if (!box->children().contains(item))
            {
                //box->addWidget(item);
                emit moved((ListItem*)item, (ListItem*)this);



                if (event->source() == this) {
                    event->setDropAction(Qt::MoveAction);
                    event->accept();

                } else {
                    event->acceptProposedAction();
                }
            }

            return;
        }
     }
    event->ignore();
}


void InnerList::dragMoveEvent(QDragMoveEvent *event)
{
    foreach(QString str, acceptedDrops)
    {
        if (event->mimeData()->hasFormat(str)) {
            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();
            } else {
                event->acceptProposedAction();
            }

        return;
        }
    }

    event->ignore();

}


void InnerList::mousePressEvent(QMouseEvent *event)
{
    QWidget *child = childAt(event->pos());

    if (child == nameLabel) // dragging whole list
    {
        QPixmap pixmap(child->size());
        child->render(&pixmap);

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << (qint64)this;

        QMimeData *mimeData = new QMimeData;
        mimeData->setData(draggableType, itemData);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - child->pos());


        QPixmap tempPixmap = pixmap;
        QPainter painter;
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();

        //child->setPixmap(tempPixmap);

        if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
            child->close();
        } else {
            child->show();
            //child->setPixmap(pixmap);
        }
    }
    /*else if (!child || !dynamic_cast<ListItem*>(child)) //dragging GUI
        return;
    */
}

void InnerList::setAcceptedDrops(QSet<QString> set)
{
    acceptedDrops = set;
}

void InnerList::setButtonText(QString text)
{
    box->addButton->setText(text);
}


void InnerList::erase()
{
    emit removed(this);
    //this->~QWidget();
}
