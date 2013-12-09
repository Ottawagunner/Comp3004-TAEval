#-------------------------------------------------
#
# Project created by QtCreator 2013-10-27T20:33:20
#
#-------------------------------------------------

QT       += core gui

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    Database.cpp \
    Controller.cpp \
    encoder.cpp \
    decoder.cpp \
    DatabaseInterface.cpp \
    DatabaseFileIO.cpp \
    Pair.cpp

HEADERS  += mainwindow.h \
    server.h \
    Database.h \
    BinaryTree.h \
    Controller.h \
    encoder.h \
    decoder.h \
    DatabaseInterface.h \
    DatabaseFileIO.h \
    Pair.h

FORMS    += mainwindow.ui
