#ifndef LISTNAME_H
#define LISTNAME_H

#include <QLabel>

class ListName : public QLabel
{
    Q_OBJECT
public:
    explicit ListName(QWidget *parent = 0);
    explicit ListName(QString name, QWidget *parent = 0);

    void mouseDoubleClickEvent(QMouseEvent *);
signals:
    void rename(QString s);
public slots:
    
private:
    bool disabled;
};

#endif // LISTNAME_H
