#-------------------------------------------------
#
# Project created by QtCreator 2015-10-25T18:16:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileExplorer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    directory.cpp \
    notdir.cpp \
    filefactory.cpp

HEADERS  += mainwindow.h \
    file.h \
    directory.h \
    notdir.h \
    filefactory.h

FORMS    += mainwindow.ui \
    file.ui

RESOURCES += \
    icons.qrc
