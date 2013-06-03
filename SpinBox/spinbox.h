#ifndef SPINBOX_H
#define SPINBOX_H


#include <QWidget>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>
#include <QMap>
#include "SignalCommunication/UserAction.h"
#include "SignalCommunication/ScoreChange.h"

namespace SpinBoxNamespace
{

class SpinBox : public QWidget
{
    Q_OBJECT
public:
    explicit SpinBox(QWidget *parent = 0);

    void setIdList(QList<IdType> &list);

signals:
    void userAction(UserAction a);

    void error(QString what);
    void warning(QString what);
    void notice(QString what);

public slots:
    void scoreChanged(ScoreChange change);

    void changeSystem(int id);
    void addSystem();
    void eraseSystem();

protected:
    // gui
    QHBoxLayout* layout;
    QVBoxLayout* plusLayout;
    QSpinBox* spinbox;
    QPushButton* plus;
    QPushButton* minus;

    // bebechy
    QMap<int, IdType> idMap;

    void handleStructureChange(ScoreChange change);
    void systemErased(IdType id);
    void systemAdded(IdType id);
};

}
#endif // SPINBOX_H
