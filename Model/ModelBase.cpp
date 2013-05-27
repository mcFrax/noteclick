#include "ModelBase.h"

using namespace Model;

ModelBase::ModelBase() :
    QObject(), children(QLinkedList<ModelBase*>())
{
}

ModelBase::ModelBase(IdRegister& registered_in, QObject* parent /*= 0*/) :
    QObject(parent), children(QLinkedList<ModelBase*>())
{
    this->idVal = registered_in.registerObject(this);
    this->registeredInVal = &registered_in;
}

ModelBase::~ModelBase()
{
}
