TEMPLATE = app

QT += qml quick sql

CONFIG += c++11

SOURCES += main.cpp \
    callmain.cpp \
    database.cpp

RESOURCES += \
    qml.qrc


# Default rules for deployment.

include(gsmcall/gsmcall.pri)

HEADERS += \
    callmain.h \
    database.h

DISTFILES +=

