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

    enum SystemChangeEnum
    {
        CreateSystemImage,   //(IdType systemId, SystemImageInfo sysImgInfo)
        CreateStaffSystem,   //(IdType systemImageId, StaffPosition position)
        CreateClef,          //(IdType staffId, StaffCoords coords, ClefType clefType)
        CreateKeySignature,  //(IdType staffId, StaffCoords coords, KeySignature signature)
        CreateTimeSignature, //(IdType staffId, StaffCoords coords, TimeSignature signature)
        CreateNote,          //(IdType staffId, StaffCoords coords, IdType voiceId, NoteValue noteValue)
        CreatePause,         //(IdType staffId, StaffCoords coords, IdType voiceId, NoteValue pauseValue)
        CreateBarcheck,      //(IdType staffId, StaffCoords coords)
        CreateSynchroMark,   //(IdType staffId, StaffCoords coords, IdType synchroId)
        CreateSlur,          //(IdType noteId1, IdType noteId2)

        MoveStaffSystem,     //(IdType staffId, StaffPosition new_position)
        MoveClef,            //(IdType clefId, StaffCoords new_coords)
        MoveKeySignature,    //(IdType keySignId, StaffCoords coords)
        MoveTimeSignature,   //(IdType timeSignId, StaffCoords coords)
        MoveNote,            //(IdType noteId, StaffCoords coords)
        MovePause,           //(IdType pauseId, StaffCoords coords)
        MoveBarcheck,        //(IdType barcheckId, StaffCoords coords)
        MoveSynchroMark,     //(IdType synchroMarkId, StaffCoords coords)

        ChangeClefType,      //(IdType clefId, ClefType new_clefType)
        ChangeKeySignature,  //(IdType keySignId, KeySignature new_signature)
        ChangeTimeSignature, //(IdType timeSignId, TimeSignature new_signature)
        ChangeNoteValue,     //(IdType noteId, NoteValue new_noteValue)
        ChangePauseValue,    //(IdType pauseId, NoteValue new_pauseValue)
        ChangeSynchroMarkId, //(IdType synchroMarkId, IdType new_synchroId)

        EraseSystemObject    //(IdType objectId)
    };

    enum StructureChangeEnum
    {
        CreateGroup,          //(IdType parent_id)
        CreateStaff,          //(IdType parent_id)
        CreateVoice,          //(IdType parent_id)
        MoveGroup,            //(IdType id, IdType new_parent_id)
        MoveStaff,            //(IdType id, IdType new_parent_id)
        MoveVoice,            //(IdType id, IdType new_parent_id)
        EraseStructureObject  //(IdType id)
    };

    enum ScoreChangeEnum
    {
        ChangeTitle           //(QString new_title)
    };

public:
    UserAction(SystemChangeEnum action, VSA args)
        : category(SystemChange), action(action), args(args)
    {
    }
    UserAction(StructureChangeEnum action, VSA args)
        : category(StructureChange), action(action), args(args)
    {
    }
    UserAction(ScoreChangeEnum action, VSA args)
        : category(ScoreChange), action(action), args(args)
    {
    }

    const ActionCategory category;
    const int action;
    const VSA args;
};

#endif // USERACTION_H
