
QT           += network widgets serialport

HEADERS       = server.h
SOURCES       = server.cpp \
                main.cpp

include(gsm/gsm.pri)
include(gsmcomm/gsmcomm.pri)

FORMS +=
