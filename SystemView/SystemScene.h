#ifndef SYSTEMSCENE_H
#define SYSTEMSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QStateMachine>

class QState;
class QString;

#include "ItemEventHandlers.h"
#include "IdRegisteredClass.h"
#include "SignalCommunication/UserAction.h"
#include "SignalCommunication/ScoreChange.h"

namespace SystemView
{

class SystemImageItem;
class SystemSceneState;
class AddStaffState;
class AddClefState;
class VoiceElementItem;

class SystemScene : public QGraphicsScene, protected IdRegisteredClass
{
    Q_OBJECT

public:
    struct MachineStates
    {
        QState *editSystem;
        QState *normalCursor;
        AddStaffState* addStaff;
        AddClefState *addClef;
        //QState *addNote;
    };

public:
    explicit SystemScene(QObject *parent = 0);
    ~SystemScene();

    const MachineStates& states() const;

    const SceneEventHandlers * handlers() const;

    using IdRegisteredClass::id;

    IdType currentVoice() const;
    
signals:
    void error(QString errorMessage);
    void warning(QString what);
    void notice(QString what);

    void userAction(UserAction);
    
public slots:
    void scoreChange(ScoreChange change);

friend class SystemSceneState;
friend class AddStaffState;
friend class AddClefState;
friend class AddNoteState;

private:
    Reg idReg;
    IdType currentVoiceVal;
    QStateMachine stateMachine;
    MachineStates statesVal;
    const SceneEventHandlers * handlersVal;
    QList<SystemImageItem*> systemImageItems;
    void setHandlers(const SceneEventHandlers * handlers);

    void setupMachine();

    void handleSystemChanged(ScoreChange change);
    void handleScoreChanged(ScoreChange change);

    void systemImageCreated(const ScoreChange& change);
    void staffSystemCreated(const ScoreChange& change);
    void clefCreated(const ScoreChange& change);

    void registerVoiceElement(IdType voiceId, VoiceElementItem * item);
};

}

#endif // SYSTEMSCENE_H
