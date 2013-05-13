#ifndef SCORECHANGE_H
#define SCORECHANGE_H

#include "VersatileSlotArgument.h"

class ScoreChange
{
public:
    //intencja uzywania dwoch enumow zamiast jednego, jest mozliwosc obslugiwania
    //w jednym miejscu tylko jednej kategorii akcji, i jednoczesnie wykorzystania
    //wlasciwosci switcha - warna o nieobslugiwanej wartosci.

    //ScoreChange ma (w przeciwienstwie do UserAction) character dokonany - model
    //oglasza, za cos sie stalo. Stad nieco inne sformulowania.

    enum ChangeCategory
    {
        SystemChange,
        StructureChange,
        ScoreChange
    };

    enum SystemChanged
    {
        StaffSystemCreated,   //(GlobalIdType id, GlobalIdType systemImageId, StaffPosition position)
        ClefCreated,          //(GlobalIdType id, GlobalIdType staffId, StaffCoords coords, ClefType clefType)
        KeySignatureCreated,  //(GlobalIdType id, GlobalIdType staffId, StaffCoords coords, KeySignature signature)
        TimeSignatureCreated, //(GlobalIdType id, GlobalIdType staffId, StaffCoords coords, TimeSignature signature)
        NoteCreated,          //(GlobalIdType id, GlobalIdType staffId, StaffCoords coords, GlobalIdType voiceId, NoteValue noteValue)
        PauseCreated,         //(GlobalIdType id, GlobalIdType staffId, StaffCoords coords, GlobalIdType voiceId, NoteValue pauseValue)
        BarcheckCreated,      //(GlobalIdType id, GlobalIdType staffId, StaffCoords coords)
        SynchroMarkCreated,   //(GlobalIdType id, GlobalIdType staffId, StaffCoords coords, GlobalIdType synchroId)
        SlurCreated,          //(GlobalIdType id, GlobalIdType noteId1, GlobalIdType noteId2)

        StaffSystemMoved,     //(GlobalIdType staffId, StaffPosition new_position)
        ClefMoved,            //(GlobalIdType clefId, StaffCoords new_coords)
        KeySignatureMoved,    //(GlobalIdType keySignId, StaffCoords coords)
        TimeSignatureMoved,   //(GlobalIdType timeSignId, StaffCoords coords)
        NoteMoved,            //(GlobalIdType noteId, StaffCoords coords)
        PauseMoved,           //(GlobalIdType pauseId, StaffCoords coords)
        BarcheckMoved,        //(GlobalIdType barcheckId, StaffCoords coords)
        SynchroMarkMoved,     //(GlobalIdType synchroMarkId, StaffCoords coords)

        ClefTypeChanged,      //(GlobalIdType clefId, ClefType new_clefType)
        KeySignatureChanged,  //(GlobalIdType keySignId, KeySignature new_signature)
        TimeSignatureChanged, //(GlobalIdType timeSignId, TimeSignature new_signature)
        NoteValueChanged,     //(GlobalIdType noteId, NoteValue new_noteValue)
        PauseValueChanged,    //(GlobalIdType pauseId, NoteValue new_pauseValue)
        SynchroMarkIdChanged, //(GlobalIdType synchroMarkId, GlobalIdType new_synchroId)

        SystemObjectErased    //(GlobalIdType objectId)
    };

    enum StructureChanged
    {
        GroupCreated,          //(GlobalIdType id, GlobalIdType parent_id)
        StaffCreated,          //(GlobalIdType id, GlobalIdType parent_id)
        VoiceCreated,          //(GlobalIdType id, GlobalIdType parent_id)
        GroupMoved,            //(GlobalIdType id, GlobalIdType new_parent_id)
        StaffMoved,            //(GlobalIdType id, GlobalIdType new_parent_id)
        VoiceMoved,            //(GlobalIdType id, GlobalIdType new_parent_id)
        StructureObjectErased  //(GlobalIdType id)
    };

    enum ScoreChanged
    {
        TitleChanged           //(QString new_title)
    };

public:
    ScoreChange(ChangeCategory category, int change, VSA args)
        : category(category), change(change), args(args)
    {
    }

    const ChangeCategory category;
    const int change;
    const VSA args;
};

#endif // SCORECHANGE_H
