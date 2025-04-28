QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apple.cpp \
    backstarenemy.cpp \
    boom.cpp \
    checkcollides.cpp \
    enemy.cpp \
    energy.cpp \
    fireenemy.cpp \
    firesuck.cpp \
    flyenemy.cpp \
    gameover.cpp \
    icemanenemy.cpp \
    icesuck.cpp \
    invincible.cpp \
    kirbypuff.cpp \
    main.cpp \
    mainwindow.cpp \
    mykirby.cpp \
    mypushbutton.cpp \
    orangeenemy.cpp \
    plantenemy.cpp \
    playscene.cpp \
    sparkenemy.cpp \
    star.cpp \
    swallowairsuck.cpp \
    swordenemy.cpp \
    win.cpp

HEADERS += \
    apple.h \
    backstarenemy.h \
    boom.h \
    checkcollides.h \
    enemy.h \
    energy.h \
    fireenemy.h \
    firesuck.h \
    flyenemy.h \
    gameover.h \
    icemanenemy.h \
    icesuck.h \
    invincible.h \
    kirbypuff.h \
    mainwindow.h \
    mykirby.h \
    mypushbutton.h \
    orangeenemy.h \
    plantenemy.h \
    playscene.h \
    sparkenemy.h \
    star.h \
    swallowairsuck.h \
    swordenemy.h \
    win.h

FORMS += \
    gameover.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
