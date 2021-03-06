#ifndef CHOIRGROUP_H
#define CHOIRGROUP_H

#include "innerlist.h"
#include "score.h"

namespace StructureView
{

class ChoirGroup : public InnerList
{
    Q_OBJECT
public:
    explicit ChoirGroup(QString name, Score *score, QWidget *parent = 0);


signals:
    
public slots:
    virtual void slotAddElement();

protected:
    void setMyStyle();
    QWidget * defaultElement();
    Score *score;

};

}
#endif // CHOIRGROUP_H
