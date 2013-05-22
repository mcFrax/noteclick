#ifndef BOX_H
#define BOX_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class Box : public QWidget
{
    Q_OBJECT
public:
    explicit Box(QWidget *parent = 0);
    explicit Box(QString name, QWidget *parent = 0);


    void paintEvent(QPaintEvent *);
    void addWidget(QWidget *widget);

    QPushButton *addButton;
signals:
    
public slots:
    void addElement(QWidget *w);

protected:


private:
    QHBoxLayout *layout;
    QVBoxLayout *listLayout;
    QVBoxLayout *outerListLayout;



    void setMyStyle();
};

#endif // BOX_H
