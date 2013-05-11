#ifndef ADDSTAFFSTATE_H
#define ADDSTAFFSTATE_H

#include <QState>

namespace SystemView
{

class SystemScene;

class AddStaffState : public QState
{
    Q_OBJECT

    void onEntry(QEvent * event);
    void onExit(QEvent * event);

    SystemScene* scene;
public:
    explicit AddStaffState(QState * parent, SystemScene *scene);
    
signals:
    
public slots:
    
};

}

#endif // ADDSTAFFSTATE_H
