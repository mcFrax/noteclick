#include "NoteItem.h"

#include <QPair>
#include <QPixmap>
#include <QColor>

#include <QMap>


using namespace SystemView;

typedef VoiceElementItem VEI;

static QPixmap pixmapActive(NoteValue);
static QPixmap pixmapInactive(NoteValue);
static QPoint translation(NoteValue);

NoteItem::NoteItem(IdRegister & reg, IdType id, IdType voiceId, StaffSystemItem *parent, NoteValue value, StaffCoords coords)
    : VEI(reg, id, voiceId, parent, pixmapActive(value), pixmapInactive(value))
{
    setPos(parent->position().fromStaffCoords(coords));
    setOffset(-translation(value).x(), -translation(value).y());
}


static QMap<QPair<double, VEI::VoiceState>, QPixmap> pixmaps;
static QMap<double, QPoint> translations;
static bool initP = 0;
static bool initT = 0;

static void loadPixmaps()
{
    pixmaps[qMakePair(4.0, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/longa.png"), Qt::yellow);
    pixmaps[qMakePair(4.0, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/longa.png"), Qt::blue);
    pixmaps[qMakePair(2.0, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/breve.png"), Qt::yellow);
    pixmaps[qMakePair(2.0, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/breve.png"), Qt::blue);
    pixmaps[qMakePair(1.0, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/1.png"), Qt::yellow);
    pixmaps[qMakePair(1.0, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/1.png"), Qt::blue);
    pixmaps[qMakePair(0.5, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/2.png"), Qt::yellow);
    pixmaps[qMakePair(0.5, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/2.png"), Qt::blue);
    pixmaps[qMakePair(0.25, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/4.png"), Qt::yellow);
    pixmaps[qMakePair(0.25, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/4.png"), Qt::blue);
    pixmaps[qMakePair(0.125, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/8.png"), Qt::yellow);
    pixmaps[qMakePair(0.125, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/8.png"), Qt::blue);
    pixmaps[qMakePair(0.0625, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/16.png"), Qt::yellow);
    pixmaps[qMakePair(0.0625, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/16.png"), Qt::blue);
    pixmaps[qMakePair(0.03125, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/32.png"), Qt::yellow);
    pixmaps[qMakePair(0.03125, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/32.png"), Qt::blue);
    pixmaps[qMakePair(0.015625, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/64.png"), Qt::yellow);
    pixmaps[qMakePair(0.015625, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/64.png"), Qt::blue);
    pixmaps[qMakePair(0.0078125, VEI::ActiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/128.png"), Qt::yellow);
    pixmaps[qMakePair(0.0078125, VEI::InactiveVoice)] = MusicItem::changeColor(QPixmap(":/nuty/nuty/128.png"), Qt::blue);
}

static void initTranslations()
{
    translations[4.0] = QPoint(15, 20);
    translations[2.0] = QPoint(15, 41);
    translations[1.0] = QPoint(15, 48);
    translations[0.5] = QPoint(13, 49);
    translations[0.25] = QPoint(13, 48);
    translations[0.125] = QPoint(12, 48);
    translations[0.0625] = QPoint(11, 49);
    translations[0.03125] = QPoint(9, 55);
    translations[0.015625] = QPoint(11, 55);
    translations[0.0078125] = QPoint(8, 48);
}

static QPixmap pixmapActive(NoteValue val)
{
    if (!initP) { loadPixmaps(); initP = 1;}
    return pixmaps.value(qMakePair(val.duration(), VEI::ActiveVoice));
}

static QPixmap pixmapInactive(NoteValue val)
{
    if (!initP) { loadPixmaps(); initP = 1;}
    return pixmaps.value(qMakePair(val.duration(), VEI::InactiveVoice));
}

static QPoint translation(NoteValue val)
{
    if (!initT) { initTranslations(); initT = 1;}
    return translations.value(val.duration());
}
