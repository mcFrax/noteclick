#ifndef IDREGISTEREDCLASS_H
#define IDREGISTEREDCLASS_H

#include <QHash>

typedef uint GlobalIdType;

template <uint IdClass>
class IdRegisteredClass
{
public:
    typedef GlobalIdType IdType;
    IdRegisteredClass()
    {
        do
            idVal = nextid++;
        while (hashmap.contains(idVal));
        hashmap.insert(idVal, this);
    }

    explicit IdRegisteredClass(IdType id)
    {
        //byc moze powinno rzucac wyjatkiem, jezli id zajete
        idVal = id;
        while (hashmap.contains(idVal))
            idVal = nextid++;
        hashmap.insert(idVal, this);
    }

    virtual ~IdRegisteredClass()
    {
        hashmap.remove(idVal);
    }

    IdType id() const
    {
        return idVal;
    }

    static IdRegisteredClass* getById(IdType id)
    {
        return hashmap.value(id);
    }

    template <typename classname>
    static classname getByIdAs(IdType id)
    {
        //cast referencji, zeby rzucal wyjatkiem przy bledzie
        return &dynamic_cast<classname>(*(hashmap.value(id)));
    }
private:
    static QHash<IdType, IdRegisteredClass*> hashmap;
    static IdType nextid;
    IdType idVal;
};

//zmienne statyczne

template<uint IdClass>
QHash<typename IdRegisteredClass<IdClass>::IdType, IdRegisteredClass<IdClass>*> IdRegisteredClass<IdClass>::hashmap;

template<uint IdClass>
typename IdRegisteredClass<IdClass>::IdType IdRegisteredClass<IdClass>::nextid = 0;

typedef IdRegisteredClass<0> ModelIdClass;
typedef ModelIdClass::IdType ModelId;

typedef IdRegisteredClass<1> SystemViewIdClass;
typedef SystemViewIdClass::IdType SystemViewId;

typedef IdRegisteredClass<2> VoiceListIdClass;
typedef VoiceListIdClass::IdType VoiceListId;


#endif // IDREGISTEREDCLASS_H
