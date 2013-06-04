#ifndef MODELBASE_H
#define MODELBASE_H

#include <QLinkedList>
#include <QObject>

#include "IdRegisteredClass.h"

class ScoreChange; // forward declaration

namespace Model {
class ScoreModel; // forward declaration

// Klasa, po ktorej dziedzicza wszystkie modele.
class ModelBase: public QObject, public IdRegisteredClass
{
    Q_OBJECT
public:
    explicit ModelBase();
//    explicit ModelBase(IdRegister& registered_in, QObject* parent = 0); // obsolete
    explicit ModelBase(ScoreModel *sm_ptr, IdRegister& registered_in, QObject* parent = 0);
    ~ModelBase();
    virtual void complementCreationList(QList<ScoreChange> *list);
protected:
    void unregister();
    ScoreModel * score_model;
    QLinkedList<ModelBase*> children;
    void emitEraseSignal();
};

}

#endif // MODELBASE_H
