#ifndef STRUCTUREMODELS_H
#define STRUCTUREMODELS_H

#include <QString>
#include "ModelBase.h"

namespace Model {

class ChoirGroup : public ModelBase
{
public slots:
    explicit ChoirGroup();
    explicit ChoirGroup(IdRegister& registered_in, QObject * parent = 0);
    ~ChoirGroup();
};

class Staff : public ModelBase
{
public slots:
    explicit Staff();
    explicit Staff(IdRegister& registered_in, QObject * parent = 0);
    ~Staff();
};

class Voice : public ModelBase
{
public slots:
    explicit Voice();
    explicit Voice(IdRegister& registered_in, QObject * parent = 0);
    ~Voice();
private:
    QString name;
};

}

#endif // STRUCTUREMODELS_H
