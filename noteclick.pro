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
    SystemView/StaffSystemItem.cpp

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
    SystemView/StaffSystemItem.h

FORMS    += mainwindow.ui
