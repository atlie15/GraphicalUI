#-------------------------------------------------
#
# Project created by QtCreator 2015-12-13T17:27:37
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    models/computer.cpp \
    models/scientist.cpp \
    repositories/computerrepository.cpp \
    repositories/linkrepository.cpp \
    repositories/scientistrepository.cpp \
    services/computerservice.cpp \
    services/linkservice.cpp \
    services/scientistservice.cpp \
    utilities/utils.cpp \
    ui/addscientistdialog.cpp \
    ui/addcomputerdialog.cpp \
    ui/addconnectiondialog.cpp \
    ui/editscientistdialog.cpp \
    ui/editcomputerdialog.cpp \
    ui/editconnectiondialog.cpp

HEADERS  += mainwindow.h \
    models/computer.h \
    models/scientist.h \
    repositories/computerrepository.h \
    repositories/linkrepository.h \
    repositories/scientistrepository.h \
    services/computerservice.h \
    services/linkservice.h \
    services/scientistservice.h \
    utilities/constants.h \
    utilities/utils.h \
    ui/addscientistdialog.h \
    ui/addcomputerdialog.h \
    ui/addconnectiondialog.h \
    ui/editscientistdialog.h \
    ui/editcomputerdialog.h \
    ui/editconnectiondialog.h

FORMS    += mainwindow.ui \
    ui/addscientistdialog.ui \
    ui/addcomputerdialog.ui \
    ui/addconnectiondialog.ui \
    ui/editscientistdialog.ui \
    ui/editcomputerdialog.ui \
    ui/editconnectiondialog.ui

INCLUDEPATH += models \
    repositories \
    services \
    ui

RESOURCES += \
    icons.qrc
