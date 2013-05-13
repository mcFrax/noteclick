#ifndef USERACTION_H
#define USERACTION_H

#include "VersatileSlotArgument.h"

class UserAction
{
public:
    //intencja uzywania dwoch enumow zamiast jednego, jest mozliwosc obslugiwania
    //w jednym miejscu tylko jednej kategorii akcji, i jednoczesnie wykorzystania
    //wlasciwosci switcha - warna o nieobslugiwanej wartosci.

    enum ActionCategory
    {
        SystemChange,
        StructureChange,
        ScoreChange
    };

    enum SystemChangeAction
    {
        CreateStaffSystem,   //(GlobalIdType systemImageId, StaffPosition position)
        CreateClef,          //(GlobalIdType staffId, StaffCoords coords, ClefType clefType)
        CreateKeySignature,  //(GlobalIdType staffId, StaffCoords coords, KeySignature signature)
        CreateTimeSignature, //(GlobalIdType staffId, StaffCoords coords, TimeSignature signature)
        CreateNote,          //(GlobalIdType staffId, StaffCoords coords, GlobalIdType voiceId, NoteValue noteValue)
        CreatePause,         //(GlobalIdType staffId, StaffCoords coords, GlobalIdType voiceId, NoteValue pauseValue)
        CreateBarcheck,      //(GlobalIdType staffId, StaffCoords coords)
        CreateSynchroMark,   //(GlobalIdType staffId, StaffCoords coords, GlobalIdType synchroId)
        CreateSlur,          //(GlobalIdType noteId1, GlobalIdType noteId2)

        MoveStaffSystem,     //(GlobalIdType staffId, StaffPosition new_position)
        MoveClef,            //(GlobalIdType clefId, StaffCoords new_coords)
        MoveKeySignature,    //(GlobalIdType keySignId, StaffCoords coords)
        MoveTimeSignature,   //(GlobalIdType timeSignId, StaffCoords coords)
        MoveNote,            //(GlobalIdType noteId, StaffCoords coords)
        MovePause,           //(GlobalIdType pauseId, StaffCoords coords)
        MoveBarcheck,        //(GlobalIdType barcheckId, StaffCoords coords)
        MoveSynchroMark,     //(GlobalIdType synchroMarkId, StaffCoords coords)

        ChangeClefType,      //(GlobalIdType clefId, ClefType new_clefType)
        ChangeKeySignature,  //(GlobalIdType keySignId, KeySignature new_signature)
        ChangeTimeSignature, //(GlobalIdType timeSignId, TimeSignature new_signature)
        ChangeNoteValue,     //(GlobalIdType noteId, NoteValue new_noteValue)
        ChangePauseValue,    //(GlobalIdType pauseId, NoteValue new_pauseValue)
        ChangeSynchroMarkId, //(GlobalIdType synchroMarkId, GlobalIdType new_synchroId)

        EraseSystemObject    //(GlobalIdType objectId)
    };

    enum StructureChangeAction
    {
        CreateGroup,          //(GlobalIdType parent_id)
        CreateStaff,          //(GlobalIdType parent_id)
        CreateVoice,          //(GlobalIdType parent_id)
        MoveGroup,            //(GlobalIdType id, GlobalIdType new_parent_id)
        MoveStaff,            //(GlobalIdType id, GlobalIdType new_parent_id)
        MoveVoice,            //(GlobalIdType id, GlobalIdType new_parent_id)
        EraseStructureObject  //(GlobalIdType id)
    };

    enum ScoreChangeAction
    {
        ChangeTitle           //(QString new_title)
    };

public:
    UserAction(ActionCategory category, int action, VSA args)
        : category(category), action(action), args(args)
    {
    }

    const ActionCategory category;
    const int action;
    const VSA args;
};

#endif // USERACTION_H
