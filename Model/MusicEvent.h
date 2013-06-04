#ifndef MUSICEVENT_H
#define MUSICEVENT_H

#include "NoteValue.h"
#include "SystemModels.h"

namespace Model {

class Voice; // forward declaration

class MusicEvent : StaffSystemElement
{
protected:
    Voice *parentVoice;
    StaffSystem *parentStaffSystem;
    NoteValue duration;
public:
    MusicEvent(ScoreModel *sm_ptr, IdRegister &registered_in, Voice * v, StaffSystem * ss, NoteValue dur = NoteValue(), StaffCoords coords = StaffCoords());
    MusicEvent(ScoreModel *sm_ptr, IdRegister &registered_in, Voice * v, StaffSystem * ss, NoteValue dur = NoteValue(), qreal coord_x = 0, qreal coord_y = 0);
    Clef * precedingClef();
    KeySignature * precedingKeySignature();
    ~MusicEvent();
};

class Note : MusicEvent
{

};

class Rest : MusicEvent
{

};

}

#endif // MUSICEVENT_H
