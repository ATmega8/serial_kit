#-------------------------------------------------
#
# Project created by QtCreator 2015-07-13T18:25:45
#
#-------------------------------------------------

QT       += core gui serialport multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serial_phone
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    framedialog.cpp \
    frameconfigure.cpp \
    framestatemachine.cpp \
    audio_output.cpp \
    audio_thread.cpp

HEADERS  += mainwindow.h \
    framedialog.h \
    frameconfigure.h \
    framestatemachine.h \
    audio_output.h \
    audio_thread.h

FORMS    += mainwindow.ui \
    framedialog.ui

DISTFILES += \
    README.md
