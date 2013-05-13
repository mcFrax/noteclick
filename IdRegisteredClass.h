#ifndef IDREGISTEREDCLASS_H
#define IDREGISTEREDCLASS_H

#include <QHash>
#include <stdexcept>

typedef uint GlobalIdType;
typedef GlobalIdType IdType;

//special id values
const IdType invalidId = IdType(0)-1;
const IdType nothingId = invalidId-1;
const IdType     anyId = nothingId-1;

bool isSpecialId(IdType id);

class BadIdException : public std::runtime_error
{
public:
    BadIdException(const char*);
};

class IdRegisteredClass;

class IdRegister
{
    friend class IdRegisteredClass;
    QHash<IdType, IdRegisteredClass*> hashmap;
    IdType nextid;
    bool freeEverythingAtDestroyVal;
protected:
    IdType registerObject(IdRegisteredClass*, IdType wantedId = anyId);
public:
    IdRegister(bool freeEverythingAtDestroy = false);
    ~IdRegister();

    IdRegisteredClass& operator[] (IdType id) const;

    IdRegisteredClass& ref(IdType id) const;

    template <typename classname>
    classname& refAs(IdType id) const
    {
        return dynamic_cast<classname>(ref(id));
    }

    IdRegisteredClass* ptr(IdType id) const;

    template <typename classname>
    classname* ptrAs (IdType id) const
    {
        return dynamic_cast<classname*>(ptr);
    }

    bool freeEverythingAtDestroy() const;
    void setFreeEverythingAtDestroy(bool);

    void unregister(IdType id);
    void unregister(IdRegisteredClass* ptr);
};

typedef IdRegister Reg;


class IdRegisteredClass
{
    friend class IdRegister;
    IdType idVal;
    IdRegister* registeredInVal;
protected:
    IdRegister& registeredIn() const;
public:
    explicit IdRegisteredClass();
    explicit IdRegisteredClass(IdRegister& reg, IdType id = anyId);

    virtual ~IdRegisteredClass();

    IdType id() const;

    void registerIn(Reg& reg, IdType id = anyId);
};


#endif // IDREGISTEREDCLASS_H
