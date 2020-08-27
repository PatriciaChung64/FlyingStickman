#-------------------------------------------------
#
# Project created by QtCreator 2019-03-21T10:11:29
#
#-------------------------------------------------

QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

TARGET = Base2A
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    coordinate.cpp \
    stickman.cpp \
    config.cpp \
    background.cpp \
    pausedialog.cpp \
    gamedialog.cpp \
    startdialog.cpp \
    stage1game.cpp \
    extendedconfig.cpp \
    stage2gamefactory.cpp \
    stage2game.cpp \
    gamestate.cpp \
    obstacle.cpp \
    entity.cpp \
    compositeentity.cpp \
    leafentity.cpp \
    player.cpp \
    stickmanplayer.cpp \
    physicsbody.cpp \
    rectcollider.cpp \
    emptyentity.cpp \
    tester.cpp \
    gamestatefactory.cpp \
    stage2gamestatefactory.cpp \
    stage3config.cpp \
    stage3gamefactory.cpp \
    stage3game.cpp \
    stage3player.cpp \
    playerstate.cpp \
    largeplayerstate.cpp \
    tinyplayerstate.cpp \
    giantplayerstate.cpp \
    stage3background.cpp \
    stage3obstacle.cpp \
    stagegoal.cpp \
    obstaclevelocityupdatevisitor.cpp \
    stagememento.cpp \
    powerup.cpp \
    powerupfactory.cpp \
    currency.cpp \
    currencyfactory.cpp \
    stage3pausedialog.cpp \
    stage3tester.cpp \
    gameobserver.cpp

HEADERS += \
    coordinate.h \
    stickman.h \
    config.h \
    background.h \
    pausedialog.h \
    gamedialog.h \
    startdialog.h \
    gamefactory.h \
    stage1gamefactory.h \
    stage1game.h \
    extendedconfig.h \
    configuration.h \
    stage2gamefactory.h \
    stage2game.h \
    gamestate.h \
    obstacle.h \
    entity.h \
    compositeentity.h \
    leafentity.h \
    player.h \
    stickmanplayer.h \
    physicsbody.h \
    rectcollider.h \
    emptyentity.h \
    tester.h \
    gamestatefactory.h \
    stage2gamestatefactory.h \
    stage3config.h \
    stage3gamefactory.h \
    stage3game.h \
    stage3player.h \
    playerstate.h \
    largeplayerstate.h \
    tinyplayerstate.h \
    giantplayerstate.h \
    stage3background.h \
    stage3obstacle.h \
    stagegoal.h \
    obstaclevelocityupdatevisitor.h \
    stagememento.h \
    powerup.h \
    powerupfactory.h \
    currency.h \
    currencyfactory.h \
    stage3pausedialog.h \
    stage3tester.h \
    gameobserver.h

FORMS += \
    pausedialog.ui \
    startdialog.ui \
    gamedialog.ui \
    stage3pausedialog.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    config.txt
