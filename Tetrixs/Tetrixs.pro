#-------------------------------------------------
#
# Project created by QtCreator 2016-01-27T10:17:41
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tetrixs
TEMPLATE = app

include(Src/ProEntry/ProEntry.pri)
include(Src/piece/piece.pri)

INCLUDEPATH += $$PWD/Src/ProEntry \
                $$PWD/Src/piece

win32:RC_FILE = Qrc/Image/icon/Tetrixs.rc

RESOURCES += \
    Qrc/Qrc.qrc
