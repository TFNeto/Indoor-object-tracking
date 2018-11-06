QT += core
QT -= gui

TARGET = opencvtest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


CONFIG += c++11 #use c++11 for compatibility
INCLUDEPATH += -I/usr/include/opencv # found in: pkg-config --cflags opencv
LIBS += -L/usr/lib/ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc#found in: pkg-config --libs opencv
LIBS += -lopencv_videoio -lopencv_video -lopencv_videostab #for videocapture
LIBS += -L/usr/local/lib #for continuityflag

SOURCES += main.cpp

