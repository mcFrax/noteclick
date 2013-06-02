#ifndef SPINBOX_H
#define SPINBOX_H


#include <QWidget>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QList>
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

public slots:
    void scoreChange(ScoreChange change);

protected:
    // gui
    QHBoxLayout* layout;
    QVBoxLayout* plusLayout;
    QSpinBox* spinbox;
    QPushButton* plus;
    QPushButton* minus;

    // bebechy
    QList<IdType> idList;

    void handleStructureChange(ScoreChange change);

};

}
#endif // SPINBOX_H
