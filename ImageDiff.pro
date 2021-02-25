#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageDiff
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/ImageLabel.cpp

HEADERS  += src/mainwindow.h \
    src/ImageLabel.h

FORMS    += ui/mainwindow.ui

win32:QMAKE_CXXFLAGS += -W3
!win32:QMAKE_CXXFLAGS += -Wall
