#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T14:09:39
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cabout.cpp \
    coption.cpp \
    boyermoore.cpp \
    setsql.cpp

HEADERS  += mainwindow.h \
    cabout.h \
    coption.h \
    boyermoore.h \
    setsql.h

FORMS    += mainwindow.ui \
    cabout.ui \
    coption.ui

RC_FILE += ico.rc
