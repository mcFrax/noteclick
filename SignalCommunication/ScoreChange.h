#ifndef SCORECHANGE_H
#define SCORECHANGE_H

#include "VersatileSlotArgument.h"
#include "IdRegisteredClass.h"

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
        SystemChanged,
        StructureChanged,
        ScoreChanged
    };

    enum SystemChangeEnum
    {
        SystemImageCreated,   //(IdType systemId, IdType systemImageId, SystemImageInfo sysImgInfo)
        StaffSystemCreated,   //(IdType id, IdType systemImageId, StaffPosition position)
        ClefCreated,          //(IdType id, IdType staffId, StaffCoords coords, ClefInfo clefInfo)
        KeySignatureCreated,  //(IdType id, IdType staffId, StaffCoords coords, KeySignature signature)
        TimeSignatureCreated, //(IdType id, IdType staffId, StaffCoords coords, TimeSignature signature)
        NoteCreated,          //(IdType id, IdType staffId, StaffCoords coords, IdType voiceId, NoteValue noteValue)
        RestCreated,         //(IdType id, IdType staffId, StaffCoords coords, IdType voiceId, NoteValue restValue)
        BarcheckCreated,      //(IdType id, IdType staffId, StaffCoords coords)
        SynchroMarkCreated,   //(IdType id, IdType staffId, StaffCoords coords, IdType synchroId)
        SlurCreated,          //(IdType id, IdType noteId1, IdType noteId2)

        StaffSystemMoved,     //(IdType staffId, StaffPosition new_position)
        ClefMoved,            //(IdType clefId, StaffCoords new_coords)
        KeySignatureMoved,    //(IdType keySignId, StaffCoords coords)
        TimeSignatureMoved,   //(IdType timeSignId, StaffCoords coords)
        NoteMoved,            //(IdType noteId, StaffCoords coords)
        RestMoved,           //(IdType restId, StaffCoords coords)
        BarcheckMoved,        //(IdType barcheckId, StaffCoords coords)
        SynchroMarkMoved,     //(IdType synchroMarkId, StaffCoords coords)

        ClefChanged,      //(IdType clefId, ClefInfo new_clefInfo)
        KeySignatureChanged,  //(IdType keySignId, KeySignature new_signature)
        TimeSignatureChanged, //(IdType timeSignId, TimeSignature new_signature)
        NoteValueChanged,     //(IdType noteId, NoteValue new_noteValue)
        RestValueChanged,    //(IdType restId, NoteValue new_restValue)
        SynchroMarkIdChanged, //(IdType synchroMarkId, IdType new_synchroId)

        SystemCreated, // (IdType id) TODO- napewno tu???
        SystemObjectErased    //(IdType objectId)
    };

    enum StructureChangeEnum
    {
        GroupCreated,          //(IdType id, IdType parent_id)
        StaffCreated,          //(IdType id, IdType parent_id)
        VoiceCreated,          //(IdType id, IdType parent_id)
        GroupMoved,            //(IdType id, IdType new_parent_id)
        StaffMoved,            //(IdType id, IdType new_parent_id)
        VoiceMoved,            //(IdType id, IdType new_parent_id)
        StructureObjectRenamed, //(IdType id, QString name)
        StructureObjectErased  //(IdType id)

    };

    enum ScoreChangeEnum
    {
        TitleChanged           //(QString new_title)
    };

public:
    ScoreChange(SystemChangeEnum change, VSA args, IdType affectedSystem = anyId)
        : category(SystemChanged), change(change), args(args), affectedSystem(affectedSystem)
    {
    }
    ScoreChange(StructureChangeEnum change, VSA args, IdType affectedSystem = noneId)
        : category(StructureChanged), change(change), args(args), affectedSystem(affectedSystem)
    {
    }
    ScoreChange(ScoreChangeEnum change, VSA args, IdType affectedSystem = noneId)
        : category(ScoreChanged), change(change), args(args), affectedSystem(affectedSystem)
    {
    }

    const ChangeCategory category;
    const int change;
    const VSA args;
    const IdType affectedSystem;
};

#endif // SCORECHANGE_H
