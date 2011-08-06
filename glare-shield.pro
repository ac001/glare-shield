# -------------------------------------------------
# Project created by QtCreator 2011-08-05T14:31:25
# -------------------------------------------------
QT += network \
    script
TARGET = glare-shield
TEMPLATE = app
SOURCES += main.cpp \
    glareshieldwidget.cpp \
    panels/autothrottlewidget.cpp \
    network/servercall.cpp \
    panels/gsbutton.cpp
HEADERS += glareshieldwidget.h \
    panels/autothrottlewidget.h \
    network/servercall.h \
    panels/gsbutton.h
RESOURCES += resources/icons.qrc
