#-------------------------------------------------
#
# Project created by QtCreator 2013-05-11T14:27:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = noteclick
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SystemView/ItemEventHandlers.cpp \
    SystemView/SystemViewItem.cpp \
    SystemView/SystemScene.cpp \
    SystemView/AddStaffState.cpp \
    SystemView/SystemImageItem.cpp

HEADERS  += mainwindow.h \
    IdRegisteredClass.h \
    SystemView/ItemEventHandlers.h \
    SystemView/SystemViewItem.h \
    SystemView/SystemScene.h \
    SystemView/AddStaffState.h \
    SystemView/SystemImageItem.h

FORMS    += mainwindow.ui
