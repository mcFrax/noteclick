#ifndef SYSTEMSCENESTATE_H
#define SYSTEMSCENESTATE_H\

#include <QState>
#include "SystemScene.h"
#include "SignalCommunication/UserAction.h"

namespace SystemView
{

/* Myślałem, że wprowadzenie tej klasy jako warstwy pośredniej wsytarczy, żeby nie friendować w scenie
 * wszystkich stanów. Ponieważ to nie wypaliło, to klasa jest mało przydatna, ale jak ją naklepałem,
 * to myślę, że zostanie. Może kiedyś się przyda do czegoś.
 */

class SystemSceneState : public QState
{
    Q_OBJECT

protected:
    SystemScene* scene;
    void sceneEmitUserAction(const UserAction& action)
    {
        scene->userAction(action);
    }
public:
    explicit SystemSceneState(QState *parent, SystemScene *scene)
        : QState(parent), scene(scene)
    {
    }
};

}


#endif // SYSTEMSCENESTATE_H
