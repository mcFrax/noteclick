#include "ModelBase.h"
#include "ScoreModel.h"
#include "VersatileSlotArgument.h"

using namespace Model;

ModelBase::ModelBase() :
    QObject(), children(QLinkedList<ModelBase*>())
{
}

ModelBase::ModelBase(ScoreModel *sm_ptr, IdRegister& registered_in, QObject* parent /*= 0*/) :
    QObject(parent), score_model(sm_ptr), children(QLinkedList<ModelBase*>())
{
    registerIn(registered_in);
}

void ModelBase::emitEraseSignal()
{
    VSA my_id = vsa(id());
    score_model->eraseStructureObject(my_id);
}

ModelBase::~ModelBase()
{
    this->emitEraseSignal();
    this->unregister();
}

void ModelBase::unregister()
{
    registeredIn().unregister(id());
}
