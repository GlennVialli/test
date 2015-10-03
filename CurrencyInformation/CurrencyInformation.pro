#-------------------------------------------------
#
# Project created by QtCreator 2015-09-28T13:33:24
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CurrencyInformation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    downloader.cpp

HEADERS  += mainwindow.h \
    downloader.h

FORMS    += mainwindow.ui

OTHER_FILES +=
