#include "IdRegisteredClass.h"


bool isSpecialId(IdType id)
{
    return id >= firstSpecialId && id <= invalidId;
}

BadIdException::BadIdException(const char * what)
    : std::runtime_error(what)
{
}


/*-------------,
|  IdRegister  |
`-------------*/

IdRegister::IdRegister(bool freeEverythingAtDestroy)
    : nextid(0), freeEverythingAtDestroyVal(freeEverythingAtDestroy)
{
}

IdRegister::~IdRegister()
{
    auto ircs = hashmap.values();
    if (freeEverythingAtDestroyVal){
        for (IdRegisteredClass* irc : ircs)
            delete irc;
    } else {
        for (IdRegisteredClass* irc : ircs)
            unregister(irc);
    }
}

IdType IdRegister::registerObject(IdRegisteredClass * ptr, IdType wantedId)
{
    if (!ptr) return invalidId;

    IdType id;
    if (wantedId == anyId){
        do
            id = nextid++;
        while (hashmap.contains(id));
    } else {
        if(isSpecialId(wantedId) || hashmap.contains(wantedId))
            throw BadIdException("Id already in use");
        id = wantedId;
    }

    hashmap.insert(id, ptr);

    return id;
}

IdRegisteredClass &IdRegister::operator [](IdType id) const
{
    return ref(id);
}

IdRegisteredClass &IdRegister::ref(IdType id) const
{
    IdRegisteredClass *ptr = hashmap.value(id, 0);
    if (!ptr) throw BadIdException("No object under id");
    return *ptr;
}

IdRegisteredClass *IdRegister::ptr(IdType id) const
{
    return hashmap.value(id, 0);
}

bool IdRegister::freeEverythingAtDestroy() const
{
    return freeEverythingAtDestroyVal;
}

void IdRegister::setFreeEverythingAtDestroy(bool b)
{
    freeEverythingAtDestroyVal = b;
}

void IdRegister::unregister(IdType id)
{
    unregister(ptr(id));
}

void IdRegister::unregister(IdRegisteredClass *obj)
{
    if (!obj || (&obj->registeredIn()) != this) return;

    IdType id = obj->id();
    obj->idVal = invalidId;
    obj->registeredInVal = 0;
    hashmap.remove(id);
}



/*--------------------,
|  IdRegisteredClass  |
`--------------------*/

IdRegisteredClass::IdRegisteredClass()
    : idVal(invalidId), registeredInVal(0)
{
}

IdRegisteredClass::IdRegisteredClass(IdRegister &reg, IdType id)
    : idVal(reg.registerObject(this, id)), registeredInVal(&reg)
{
}

IdRegisteredClass::~IdRegisteredClass()
{
    if (registeredInVal) registeredInVal->unregister(this);
}

IdType IdRegisteredClass::id() const
{
    return idVal;
}

IdRegister &IdRegisteredClass::registeredIn() const
{
    return *registeredInVal;
}

void IdRegisteredClass::registerIn(Reg &reg, IdType id)
{
    if (registeredInVal) registeredInVal->unregister(this);
    idVal = reg.registerObject(this, id);
    registeredInVal = &reg;
}


