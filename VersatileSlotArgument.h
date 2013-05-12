#ifndef VERSATILESLOTARGUMENT_H
#define VERSATILESLOTARGUMENT_H

#include <QExplicitlySharedDataPointer>
#include <QSharedData>

#include <tuple>

//===============================================================//
//Uzycie:
//  vsa(argumenty...) do tworzenia VSA,
//  VSA::unpackTo(zmienne...) do rozpakowywania.
//
//Przyklad:
//  VSA args = vsa(1, 0.2, QString("Pafnucy"));
//
//  int a; double d; QString s;
//
//  args.unpackTo(a, d, s);
//
//Uwaga:
//  Rozpakowywanie jest koszmarnie wrazliwe na niezgodnosc typow,
//  w szczegolnosci T != T&.
//
//===============================================================//

//Dodaje polimorfizm do QSharedData
class VersatileSlotArgumentDataCommonBase : public QSharedData
{
public:
    virtual ~VersatileSlotArgumentDataCommonBase() {}
};

class VersatileSlotArgument;

template <typename ... Args>
class VersatileSlotArgumentData : public VersatileSlotArgumentDataCommonBase, public std::tuple<Args...>
{
    template <typename... FArgs>
    friend VersatileSlotArgument vsa(const FArgs & ... args);

    VersatileSlotArgumentData(const Args & ...args)
        : std::tuple<Args...>(args...)
    {
    }
};

class VersatileSlotArgument
{
    template <typename... Args>
    friend VersatileSlotArgument vsa(const Args & ... args);
    QExplicitlySharedDataPointer<VersatileSlotArgumentDataCommonBase> dpointer;
    VersatileSlotArgument(VersatileSlotArgumentDataCommonBase* vsad)
        : dpointer(vsad)
    {
    }

public:
    template <typename... Args>
    void unpackTo(Args&... args) const
    {
        VersatileSlotArgumentDataCommonBase& data = *(dpointer.data());
        VersatileSlotArgumentData<Args...>& vsad =
                dynamic_cast<VersatileSlotArgumentData<Args...>&>(data);
        std::tuple<Args...>& tup =
                dynamic_cast<std::tuple<Args...>&>(vsad);
        std::tie(args...) = tup;
    }
};

typedef VersatileSlotArgument VSA;

template <typename... Args>
VSA vsa(const Args & ... args)
{
    return VSA(new VersatileSlotArgumentData<Args...>(args...));
}


#endif // VERSATILESLOTARGUMENT_H
