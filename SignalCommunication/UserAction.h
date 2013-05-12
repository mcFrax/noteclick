#ifndef USERACTION_H
#define USERACTION_H

#include "VersatileSlotArgument.h"

class UserAction
{
public:
    enum ActionCategory
    {
        SystemChange,
        StructureChange
    };
    enum SystemChangeAction
    {
    };
    enum StructureChangeAction
    {
    };

    const VSA args;
};

#endif // USERACTION_H
