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

class InnerList : public ListItem
{
    Q_OBJECT
public:
    explicit InnerList(QString name, QWidget *parent = 0);

    void addElement(ListItem *element);
    virtual void setText(QString name);

signals:
    void moved(ListItem* element, ListItem* parent);

public slots:
    void toggle();
    //void addWidget(QWidget *widget);
    void addElement();
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

#endif // INNERLIST_H
