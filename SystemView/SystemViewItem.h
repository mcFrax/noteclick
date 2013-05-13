#ifndef SYSTEMVIEWITEM_H
#define SYSTEMVIEWITEM_H

#include "IdRegisteredClass.h"

namespace SystemView
{

//!Na razie ta klasa nic nie dodaje do IdRegisteredClass, ale to sie moze zmienic
class SystemViewItem : public IdRegisteredClass
{
public:
    SystemViewItem(IdRegister &, IdType id = anyId);
};

}

#endif // SYSTEMVIEWITEM_H
