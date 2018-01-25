#-------------------------------------------------
#
# Project created by QtCreator 2016-11-25T20:47:24
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network serialport

TARGET = GUI
TEMPLATE = app

HEADERS += \
    joystick/joystick.h \
    joystick/common.h \
    joystick/state.h \
    joystick/pipeline.h \
    joystick/button.h \
    joystick/axis.h \
    joystick/backend/base.h \
    joystick/backend/sfml.h \
    joystick/mode/base.h \
    joystick/mode/drive.h \
    joystick/mode/rotation.h \
    copilotscreen.h \
    joystick/mode/general.h \
    arduino.h \
    connection/connection.h \
    UIWidgets/indicator.h \
    UIWidgets/missions.h \
    UIWidgets/modeList.h \
    UIWidgets/statusbar.h \
    UIWidgets/timer.h \
    UIWidgets/basicwidget.h \
    UIWidgets/rotatablelabel.h \
    UIWidgets/qcontainer.h

SOURCES += \
    main.cpp \
    copilotscreen.cpp \
    joystick/joystick.cpp \
    joystick/backend/base_backend.cpp \
    joystick/mode/base_mode.cpp \
    connection/connection.cpp \
    UIWidgets/qcontainer.cpp

FORMS += \
    copilotscreen.ui

CONFIG += c++11 c++17

unix {
  CONFIG+= link_pkgconfig
  PKGCONFIG += sfml-window
}
