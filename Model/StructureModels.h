#ifndef STRUCTUREMODELS_H
#define STRUCTUREMODELS_H

#include <QString>
#include "ModelBase.h"

namespace Model {

class ChoirGroup : public ModelBase
{
private:
    explicit ChoirGroup();
public:
    explicit ChoirGroup(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent = 0);
    ~ChoirGroup();
};

class Staff : public ModelBase
{
private:
    explicit Staff();
public:
    explicit Staff(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent = 0);
    ~Staff();
};

class Voice : public ModelBase
{
private:
    QString name;

public:
    explicit Voice();
    explicit Voice(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent = 0);
    ~Voice();
};

}

#endif // STRUCTUREMODELS_H
