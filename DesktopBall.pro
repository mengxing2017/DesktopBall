#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T09:31:24
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DesktopBall
TEMPLATE = app


SOURCES += main.cpp\
        ui/desktopball.cpp \
    server/netspeed.cpp \
    server/systeminfo.cpp \
    ui/showinfo.cpp

HEADERS  += ui/desktopball.h \
    server/netspeed.h \
    server/systeminfo.h \
    ui/showinfo.h

RESOURCES += \
    res.qrc

DISTFILES +=
