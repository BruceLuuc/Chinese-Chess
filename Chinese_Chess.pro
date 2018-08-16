HEADERS += \
    Board.h \
    Stone.h

SOURCES += \
    Board.cpp \
    main.cpp \
    Stone.cpp

QT+=widgets gui
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
