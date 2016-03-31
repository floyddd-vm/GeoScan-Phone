INCLUDEPATH += $$PWD
DEFINES += GSM_LIBRARY

SOURCES += \
    $$PWD/gsmmodem.cpp \
    $$PWD/gsmsmsreader.cpp \
    $$PWD/gsmsmssender.cpp \
    $$PWD/qcbsmessage.cpp \
    $$PWD/qsmsmsmessage.cpp


HEADERS += \
    $$PWD/gsmsmsreader.hpp \
    $$PWD/gsmsmssender.hpp \
    $$PWD/qcbsmessage.hpp \
    $$PWD/qsmsmessage.hpp \
    $$PWD/qsmsmessage_p.h \
    $$PWD/qtelephonynamespace.h \
    $$PWD/gsmmodem.h

