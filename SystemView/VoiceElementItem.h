#ifndef VOICEELEMENTITEM_H
#define VOICEELEMENTITEM_H

#include "MusicItem.h"
#include "IdRegisteredClass.h"
#include "SystemViewItem.h"
#include "StaffSystemItem.h"

namespace SystemView
{

class VoiceElementItem : public MusicItem, public SystemViewItem
{
public:
    enum VoiceState
    {
        ActiveVoice,
        InactiveVoice,
    };

    VoiceElementItem(IdRegister &, IdType id, IdType voiceId, StaffSystemItem *parent, QPixmap active, QPixmap inactive);
    const IdType voiceId;
    void setState(VoiceState state);
protected:
    SystemScene * systemScene();
    QPixmap active;
    QPixmap inactive;
};

}

#endif // VOICEELEMENTITEM_H
