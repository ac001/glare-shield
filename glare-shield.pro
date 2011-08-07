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
    widgets/gsbutton.cpp \
    panels/altitudewidget.cpp \
    widgets/gsreadoutwidget.cpp \
    widgets/xlabel.cpp \
    widgets/xdigit.cpp \
    panels/headingwidget.cpp \
    panels/landinggearwidget.cpp
HEADERS += glareshieldwidget.h \
    panels/autothrottlewidget.h \
    network/servercall.h \
    widgets/gsbutton.h \
    panels/altitudewidget.h \
    widgets/gsreadoutwidget.h \
    widgets/xlabel.h \
    widgets/xdigit.h \
    panels/headingwidget.h \
    panels/landinggearwidget.h
RESOURCES += resources/icons.qrc
