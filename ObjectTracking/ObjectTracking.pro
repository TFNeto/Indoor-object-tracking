#-------------------------------------------------
#
# Project created by QtCreator 2018-11-24T14:19:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ObjectTracking
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 #use c++11 for compatibility
INCLUDEPATH += -I/usr/include/opencv # found in: pkg-config --cflags opencv
LIBS += -L/usr/lib/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc#found in: pkg-config --libs opencv
LIBS += -lopencv_videoio -lopencv_video -lopencv_videostab #for videocapture
LIBS += -L/usr/local/lib #for continuityflag
LIBS += -lboost_system

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    configuration.cpp \
    calibrate.cpp \
    realtimetracking.cpp \
    camera.cpp \
    trackinglog.cpp \
    marker.cpp \
    objectdetection.cpp

HEADERS += \
        mainwindow.h \
    calibrate.h \
    configuration.h \
    realtimetracking.h \
    camera.h \
    trackinglog.h \
    marker.h \
    serial.h

FORMS += \
        mainwindow.ui \
    calibrate.ui \
    configuration.ui \
    realtimetracking.ui \
    trackinglog.ui
