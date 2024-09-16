TEMPLATE = app
TARGET = NvControl
DEPENDPATH += .
INCLUDEPATH += .
QT += core5compat 
QT += network widgets charts #script
CONFIG += crypto

# Input
HEADERS += MainWindow.h
FORMS += NvControl.ui
SOURCES += Main.cpp MainWindow.cpp
RESOURCES += Ressources.qrc

#linux-g++:LIBS += -L/usr/lib -lssl -lcrypto
# win32-msvc2010:LIBS += libmpdclient.dll.a


