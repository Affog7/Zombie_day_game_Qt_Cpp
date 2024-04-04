greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    animation.cpp \
    bullet.cpp \
    character.cpp \
    entity.cpp \
    game.cpp \
    gameobject.cpp \
    gamescene.cpp \
    helper.cpp \
    main.cpp \
    player.cpp \
    view.cpp \
    zombieday.cpp

HEADERS += \
    ObjectType.h \
    animation.h \
    bullet.h \
    character.h \
    entity.h \
    game.h \
    gameobject.h \
    gamescene.h \
    helper.h \
    player.h \
    view.h \
    zombieday.h

RESOURCES += \
    resource.qrc

QT += core
