#ifndef NOTEITEM_H
#define NOTEITEM_H

#include "VoiceElementItem.h"

#include "NoteValue.h"
#include "StaffCoords.h"

namespace SystemView
{

class NoteItem : public VoiceElementItem
{
public:
    NoteItem(IdRegister &, IdType id, IdType voiceId, StaffSystemItem *parent, NoteValue value, StaffCoords coords);
    NoteValue value;
    StaffCoords coords;
};

}

#endif // NOTEITEM_H
