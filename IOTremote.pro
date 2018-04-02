#-------------------------------------------------
#
# Project created by QtCreator 2018-04-01T15:23:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IOTremote
TEMPLATE = app


SOURCES += main.cpp \
    udpclient.cpp

HEADERS  += \
    udpclient.h
