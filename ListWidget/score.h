#ifndef SCORE_H
#define SCORE_H


#include "listwidget.h"
#include "SignalCommunication/UserAction.h"
#include "SignalCommunication/ScoreChange.h"
class VoiceWidget;

class Score : public ListWidget
{
    Q_OBJECT
public:
    explicit Score(QWidget *parent = 0, QString name = "Voice List");

signals:
    void error(QString what);
    void warning(QString what);
    void notice(QString what);

    void userAction(UserAction a);

    void voiceCheckedSignal(IdType, bool);
    void voiceSelectedSignal(IdType);
    //TMP
    /*
    void modelElementRemoved(IdType id);
    void modelElementRenamed(IdType id, QString name);
    void modelElementMoved(IdType id, IdType pid);
    */
public slots:

    void scoreChange(ScoreChange sc);

    // inner slots
    void elementRemoved(ListItem *item);
    void elementRenamed(ListItem *item, QString name);
    void elementMoved(ListItem *id, ListItem *to);
    void elementAdded(UserAction::StructureChangeEnum, ListItem *pid);
    void slotAddElement();

    void voiceSelected(void *p, bool state);
    void voiceChecked(void *p, bool state);
    /*

    void voiceClicked(IdType id);
    */

protected:
    QWidget * defaultElement();

    QMap<IdType, void*> pointers;

    void addChoirGroup(IdType id, IdType parentId, QString name="ChoirGroup");
    void addStaff(IdType id, IdType parentId, QString name="Staff");
    void addVoice(IdType id, IdType parentId, QString name="Voice");

    void renameElement(IdType id, QString name);

    void moveElement(IdType id, IdType newParent);

    void removeElement(IdType id);

    void handleStructureChange(ScoreChange change);

    VoiceWidget *selected;
};

#endif // SCORE_H
