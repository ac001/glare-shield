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
    widgets/xgroupboxes.cpp \
    widgets/xlabel.cpp \
    widgets/xdigit.cpp
HEADERS += glareshieldwidget.h \
    panels/autothrottlewidget.h \
    network/servercall.h \
    widgets/gsbutton.h \
    panels/altitudewidget.h \
    widgets/gsreadoutwidget.h \
    widgets/xgroupboxes.h \
    widgets/xlabel.h \
    widgets/xdigit.h
RESOURCES += resources/icons.qrc
