#ifndef MODELBASE_H
#define MODELBASE_H

#include <QLinkedList>
#include <QObject>

//#include "ScoreModel.h" // pieprzy sie przez to
#include "IdRegisteredClass.h"

namespace Model {

// Klasa, po ktorej dziedzicza wszystkie modele.
class ModelBase: public QObject, public IdRegisteredClass
{
    Q_OBJECT
public:
    explicit ModelBase();
    explicit ModelBase(IdRegister& registered_in, QObject* parent = 0);
    ~ModelBase();
protected:
    void unregister();
//    ScoreModel * score_model;
    QLinkedList<ModelBase*> children;
};

}

#endif // MODELBASE_H
