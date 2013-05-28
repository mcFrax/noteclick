#include "ModelBase.h"

using namespace Model;

ModelBase::ModelBase() :
    QObject(), children(QLinkedList<ModelBase*>())
{
}

ModelBase::ModelBase(IdRegister& registered_in, QObject* parent /*= 0*/) :
    QObject(parent), children(QLinkedList<ModelBase*>())
{
    registerIn(registered_in);
}

ModelBase::~ModelBase()
{
    this->unregister();
}

void ModelBase::unregister()
{
    registeredIn().unregister(id());
}
