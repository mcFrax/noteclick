#include "NoteItem.h"

#include <QHash>
#include <QPair>
#include <QPixmap>


using namespace SystemView;

typedef VoiceElementItem VEI;

static QPixmap pixmapActive(NoteValue);

NoteItem::NoteItem(IdRegister & reg, IdType id, IdType voiceId, StaffSystemItem *parent, NoteValue value, StaffCoords coords)
    : VEI(reg, id, voiceId, parent, pixmapActive(value), pixmapInactive(value))
{
}


static QHash<QPair<double, VEI::VoiceState, QPixmap> pixmaps;
