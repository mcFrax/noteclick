#ifndef STAFF_H
#define STAFF_H

#include "innerlist.h"

#include "score.h"
class Staff : public InnerList
{
    Q_OBJECT
public:
    explicit Staff(QString name, Score *score, QWidget *parent = 0);
    
signals:
    
public slots:
    
protected:
    QWidget * defaultElement();
    Score *score;

};

#endif // STAFF_H
