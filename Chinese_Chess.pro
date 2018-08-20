HEADERS += \
    Board.h \
    Stone.h \
    SingleGame.h \
    Step.h \
    NetGame.h

SOURCES += \
    Board.cpp \
    main.cpp \
    Stone.cpp \
    SingleGame.cpp \
    NetGame.cpp

QT       +=widgets gui
QT       += core gui
QT       +=network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
