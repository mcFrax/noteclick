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
        CreateClef,          //(IdType staffId, StaffCoords coords, ClefInfo clefInfo)
        CreateKeySignature,  //(IdType staffId, StaffCoords coords, KeySignature signature)
        CreateTimeSignature, //(IdType staffId, StaffCoords coords, TimeSignature signature)
        CreateNote,          //(IdType staffId, StaffCoords coords, IdType voiceId, NoteValue noteValue)
        CreateRest,         //(IdType staffId, StaffCoords coords, IdType voiceId, NoteValue restValue)
        CreateBarcheck,      //(IdType staffId, StaffCoords coords)
        CreateSynchroMark,   //(IdType staffId, StaffCoords coords, IdType synchroId)
        CreateSlur,          //(IdType noteId1, IdType noteId2)

        MoveStaffSystem,     //(IdType staffId, StaffPosition new_position)
        MoveClef,            //(IdType clefId, StaffCoords new_coords)
        MoveKeySignature,    //(IdType keySignId, StaffCoords coords)
        MoveTimeSignature,   //(IdType timeSignId, StaffCoords coords)
        MoveNote,            //(IdType noteId, StaffCoords coords)
        MoveRest,           //(IdType restId, StaffCoords coords)
        MoveBarcheck,        //(IdType barcheckId, StaffCoords coords)
        MoveSynchroMark,     //(IdType synchroMarkId, StaffCoords coords)

        ChangeClef,      //(IdType clefId, ClefInfo new_clefInfo)
        ChangeKeySignature,  //(IdType keySignId, KeySignature new_signature)
        ChangeTimeSignature, //(IdType timeSignId, TimeSignature new_signature)
        ChangeNoteValue,     //(IdType noteId, NoteValue new_noteValue)
        ChangeRestValue,    //(IdType restId, NoteValue new_restValue)
        ChangeSynchroMarkId, //(IdType synchroMarkId, IdType new_synchroId)

        CreateSystem, //(int position)
        ChangeSystem, //(IdType id)
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
        StructureObjectRename, //(Idtype id, QString name)
        StructureObjectErase  //(IdType id)

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
