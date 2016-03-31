INCLUDEPATH += $$PWD
DEFINES += GSM_LIBRARY

HEADERS += \
    $$PWD/qatchat.h \
    $$PWD/qatchat_p.h \
    $$PWD/qatchatscript.h \
    $$PWD/qatresult.h \
    $$PWD/qatresultparser.h \
    $$PWD/qatutils.h \
    $$PWD/qgsmcodec.h \
    $$PWD/qprefixmatcher_p.h \
    $$PWD/qretryatchat.h

SOURCES += \
    $$PWD/qatchat.cpp \
    $$PWD/qatchatscript.cpp \
    $$PWD/qatresult.cpp \
    $$PWD/qatresultparser.cpp \
    $$PWD/qatutils.cpp \
    $$PWD/qgsmcodec.cpp \
    $$PWD/qprefixmatcher.cpp \
    $$PWD/qretryatchat.cpp
