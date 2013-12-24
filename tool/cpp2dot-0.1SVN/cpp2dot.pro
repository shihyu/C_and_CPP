TEMPLATE	= app
TARGET		= cpp2dot

#QMAKE_CFLAGS+=-pg
#QMAKE_CXXFLAGS+=-pg
#QMAKE_LFLAGS+=-pg
DESTDIR         = ./bin
INCLUDEPATH	+= . 
DEPENDPATH	+= .
LIBS	        =
OBJECTS_DIR	= .

SOURCES += *.cpp
HEADERS += *.h

QT -= gui

unix {
    target.path=$$[QT_INSTALL_BINS]
    INSTALLS += target
}
