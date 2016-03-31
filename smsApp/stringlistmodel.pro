QT += qml quick sql

SOURCES += main.cpp \
    dialogobject.cpp \
    smsmain.cpp


include(DB/gsmdb.pri)
target.path = $$[QT_INSTALL_EXAMPLES]/quick/models/stringlistmodel
INSTALLS += target

DISTFILES += \
    DB/Contacts.sqlite \
    images/ArrowLeft.png

HEADERS += \
    dialogobject.h \
    smsmain.h

RESOURCES += \
    main.qrc
