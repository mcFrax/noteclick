#-------------------------------------------------
#
# Project created by QtCreator 2013-05-11T14:27:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = noteclick
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -std=c++11


SOURCES +=\    
    ClefInfo.cpp \
    CuteMenu.cpp \
    IdRegisteredClass.cpp \
    ListWidget/box.cpp \
    ListWidget/choirgroup.cpp \
    ListWidget/erasebutton.cpp \
    ListWidget/innerlist.cpp \
    ListWidget/listitem.cpp \
    ListWidget/listname.cpp \
    ListWidget/listwidget.cpp \
    ListWidget/score.cpp \
    ListWidget/staff.cpp \
    ListWidget/voicewidget.cpp \
    Main.cpp \
    MainWindow.cpp \
    Model/ScoreModel.cpp \
    Model/ScoreModel-structure.cpp \
    Model/ScoreModel-system.cpp \
    NoteValue.cpp \
    StaffCoords.cpp \
    SystemImageInfo.cpp \
    SystemView/AddClefState.cpp \
    SystemView/AddNoteState.cpp \
    SystemView/AddStaffState.cpp \
    SystemView/ClefItem.cpp \
    SystemView/ClefMenu.cpp \
    SystemView/ItemEventHandlers.cpp \
    SystemView/MusicItem.cpp \
    SystemView/NoteMenu.cpp \
    SystemView/StaffSystemItem.cpp \
    SystemView/SystemImageItem.cpp \
    SystemView/SystemScene.cpp \
    SystemView/SystemViewItem.cpp \
    SystemView/VoiceElementItem.cpp \
    SystemView/NoteItem.cpp \
    Model/SystemModels.cpp \
    Model/StructureModels.cpp \
    Model/ModelBase.cpp

HEADERS  += \
    ClefInfo.h \
    CuteMenu.h \
    IdRegisteredClass.h \
    ListWidget/box.h \
    ListWidget/choirgroup.h \
    ListWidget/erasebutton.h \
    ListWidget/innerlist.h \
    ListWidget/listitem.h \
    ListWidget/listname.h \
    ListWidget/listwidget.h \
    ListWidget/score.h \
    ListWidget/staff.h \
    ListWidget/voicewidget.h \
    MainWindow.h \
    Model/ScoreModel.h \
    NoteValue.h \
    SignalCommunication/ScoreChange.h \
    SignalCommunication/UserAction.h \
    StaffCoords.h \
    SystemImageInfo.h \
    SystemView/AddClefState.h \
    SystemView/AddNoteState.h \
    SystemView/AddStaffState.h \
    SystemView/ClefItem.h \
    SystemView/ClefMenu.h \
    SystemView/ItemEventHandlers.h \
    SystemView/MusicItem.h \
    SystemView/NoteMenu.h \
    SystemView/StaffSystemItem.h \
    SystemView/SystemImageItem.h \
    SystemView/SystemScene.h \
    SystemView/SystemSceneState.h \
    SystemView/SystemViewItem.h \
    SystemView/VoiceElementItem.h \
    VersatileSlotArgument.h \
    SystemView/NoteItem.h \
    Model/SystemModels.h \
    Model/StructureModels.h \
    Model/ModelBase.h

FORMS    += mainwindow.ui

RESOURCES += \
    nuty.qrc \
    icons.qrc
