#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T14:25:40
#
#-------------------------------------------------

QT       += core gui
QT += qml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QueueingModel
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
    joint.cpp \
    scenesystem.cpp \
    mainwindow.cpp \
    modelview.cpp \
    request.cpp \
    randomgenerator.cpp \
    ElementsSystem/elementsystem.cpp \
    ElementsSystem/fifoqueue.cpp \
    ElementsSystem/inputstream.cpp \
    ElementsSystem/lifoqueue.cpp \
    ElementsSystem/outputstream.cpp \
    ElementsSystem/queueSystem.cpp \
    ElementsSystem/siroqueue.cpp \
    ElementsSystem/device.cpp \
    Dialogs/dialogdevice.cpp \
    Dialogs/dialogoutputstream.cpp \
    Dialogs/dialogqueue.cpp

HEADERS  += \
    joint.h \
    scenesystem.h \
    mainwindow.h \
    modelview.h \
    randomgenerator.h \
    request.h \
    ElementsSystem/elementsystem.h \
    ElementsSystem/fifoqueue.h \
    ElementsSystem/inputstream.h \
    ElementsSystem/lifoqueue.h \
    ElementsSystem/outputstream.h \
    ElementsSystem/queueSystem.h \
    ElementsSystem/siroqueue.h \
    ElementsSystem/device.h \
    Dialogs/dialogdevice.h \
    Dialogs/dialogoutputstream.h \
    Dialogs/dialogqueue.h

FORMS += \
    mainwindow.ui \
    Dialogs/dialogdevice.ui \
    Dialogs/dialogoutputstream.ui \
    Dialogs/dialogqueue.ui

RESOURCES += \
    res.qrc
