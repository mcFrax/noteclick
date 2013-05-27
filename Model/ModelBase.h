#ifndef MODELBASE_H
#define MODELBASE_H

#include <QLinkedList>
#include <QObject>

#include "IdRegisteredClass.h"

//#define NullModel = 0; // pointer

namespace Model {

// Klasa, po ktorej dziedzicza wszystkie modele.
class ModelBase: public QObject, public IdRegisteredClass
{
public:
    explicit ModelBase();
    explicit ModelBase(IdRegister& registered_in, QObject* parent = 0);
    ~ModelBase();
private:
    Q_OBJECT
    QLinkedList<ModelBase*> children;
};

}

#endif // MODELBASE_H
