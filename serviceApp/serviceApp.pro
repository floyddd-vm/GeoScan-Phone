
QT           += network widgets serialport sql
HEADERS       = \
    server.h \
    sockext.h
SOURCES       = server.cpp \
                main.cpp \
    sockext.cpp

CONFIG+= c++11//хуй
include(gsm/gsm.pri)
include(gsmcomm/gsmcomm.pri)
include(DB/gsmdb.pri)
include(sms/sms.pri)
