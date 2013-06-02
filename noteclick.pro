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
    SystemView/ItemEventHandlers.cpp \
    SystemView/SystemViewItem.cpp \
    SystemView/SystemScene.cpp \
    SystemView/AddStaffState.cpp \
    SystemView/SystemImageItem.cpp \
    Model/ScoreModel.cpp \
    StaffCoords.cpp \
    IdRegisteredClass.cpp \
    Model/ScoreModel-structure.cpp \
    Model/ScoreModel-system.cpp \
    Main.cpp \
    MainWindow.cpp \
    SystemImageInfo.cpp \
    ListWidget/voicewidget.cpp \
    ListWidget/staff.cpp \
    ListWidget/score.cpp \
    ListWidget/listwidget.cpp \
    ListWidget/listname.cpp \
    ListWidget/listitem.cpp \
    ListWidget/innerlist.cpp \
    ListWidget/erasebutton.cpp \
    ListWidget/choirgroup.cpp \
    ListWidget/box.cpp \
    SpinBox/spinbox.cpp

HEADERS  += \
    IdRegisteredClass.h \
    SystemView/ItemEventHandlers.h \
    SystemView/SystemViewItem.h \
    SystemView/SystemScene.h \
    SystemView/AddStaffState.h \
    SystemView/SystemImageItem.h \
    Model/ScoreModel.h \
    VersatileSlotArgument.h \
    SignalCommunication/UserAction.h \
    SignalCommunication/ScoreChange.h \
    StaffCoords.h \
    MainWindow.h \
    SystemView/SystemSceneState.h \
    SystemImageInfo.h \
    ListWidget/voicewidget.h \
    ListWidget/staff.h \
    ListWidget/score.h \
    ListWidget/listwidget.h \
    ListWidget/listname.h \
    ListWidget/listitem.h \
    ListWidget/innerlist.h \
    ListWidget/erasebutton.h \
    ListWidget/choirgroup.h \
    ListWidget/box.h \
    SpinBox/spinbox.h \
    spinbox.h

FORMS    += mainwindow.ui
