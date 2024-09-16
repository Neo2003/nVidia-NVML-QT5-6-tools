TEMPLATE = app
TARGET = NvControl
DEPENDPATH += .
INCLUDEPATH += .
QT += core5compat 
QT += network widgets charts
CONFIG += crypto

# Input
HEADERS += MainWindow.h
FORMS += NvControl.ui
SOURCES += Main.cpp MainWindow.cpp
RESOURCES += Ressources.qrc
