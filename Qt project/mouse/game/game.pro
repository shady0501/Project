QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    levelscene.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mouse.cpp \
    mybutton.cpp \
    playscene.cpp \
    timer.cpp

HEADERS += \
    levelscene.h \
    mainwindow.h \
    map.h \
    mouse.h \
    mybutton.h \
    playscene.h \
    timer.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    Map/level1.txt \
    Map/level2.txt \
    Map/level3.txt \
    Map/level4.txt \
    Map/level5.txt \
    icon/BABA.png \
    icon/BABA_word.png \
    icon/FLAG.png \
    icon/IS.png \
    icon/PATH.png \
    icon/PLAG_word.png \
    icon/PUSH.png \
    icon/ROCK.png \
    icon/ROCK_word.png \
    icon/STOP.png \
    icon/WALL.png \
    icon/WALL_word.png \
    icon/WIN.png \
    icon/YOU.png
