#ifndef INNERLIST_H
#define INNERLIST_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QSet>


#include "box.h"
#include "listname.h"
#include "listitem.h"

namespace StructureView
{

class InnerList : public ListItem
{
    Q_OBJECT
public:
    explicit InnerList(QString name, QWidget *parent = 0);


    virtual void setText(QString name);
    void addElement(ListItem *element);

signals:
    void moved(ListItem* element, ListItem* parent);

public slots:
    void toggle();
    virtual void slotAddElement();
    void erase();

protected:
    QVBoxLayout *layout;
    QPushButton *plusButton;
    QPushButton *eraseButton;
    Box *box;
    QHBoxLayout *headerLayout;
    QLineEdit *nameEdit;
    ListName *nameLabel;

    QSet<QString> acceptedDrops;

    void  setButtonText(QString);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *);
    virtual void dropEvent(QDropEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);

    virtual QWidget *defaultElement();
    virtual void setMyStyle();

    virtual void setAcceptedDrops(QSet<QString> set);

private:
    bool hidden;
    
};

}

#endif // INNERLIST_H
