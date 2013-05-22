#ifndef SCORE_H
#define SCORE_H

#include "listwidget.h"
#include "SignalCommunication/UserAction.h"
#include "SignalCommunication/ScoreChange.h"

class Score : public ListWidget
{
    Q_OBJECT
public:
    //explicit Score(QWidget *parent = 0);
    explicit Score(QWidget *parent = 0, QString name = "bla");

signals:
    void error(QString what);
    void warning(QString what);
    void notice(QString what);

    void userAction(UserAction a);

    //TMP

    void modelElementRemoved(IdType id);
    void modelElementRenamed(IdType id, QString name);
    void modelElementMoved(IdType id, IdType pid);
public slots:

    void scoreChange(ScoreChange sc);

    //TMP
    void addElement();


    void elementRemoved(ListItem *item);

    void elementRenamed(ListItem *item, QString name);
    void elementMoved(ListItem *id, ListItem *to);

  /*  void voiceClicked(IdType id);
    */

protected:
    QWidget * defaultElement();

    QMap<IdType, void*> pointers;

    void addChoirGroup(IdType id, IdType parentId, QString name="ChoirGroup");
    void addStaff(IdType id, IdType parentId, QString name="Staff");
    void addVoice(IdType id, IdType parentId, QString name="Voice");

    void renameElement(IdType id, QString name);

//    void moveChoirGroup(IdType id, IdType oldParent, IdType newParent);
    void moveElement(IdType id, IdType newParent);

    void removeElement(IdType id);

    void handleStructureChange(ScoreChange change);
};

#endif // SCORE_H
