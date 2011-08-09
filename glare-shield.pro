TEMPLATE = app
TARGET = glare-shield
DEPENDPATH += .
INCLUDEPATH += .
QT += network \
    script
HEADERS += panels/landinggearwidget.h \
    panels/headingwidget.h \
    panels/flapswidget.h \
    panels/chatwidget.h \
    panels/autothrottlewidget.h \
    panels/altitudewidget.h \
    network/servercall.h \
    glareshieldwidget.h \
    widgets/xlabel.h \
    widgets/xdigit.h \
    widgets/gsreadoutwidget.h \
    widgets/gsbutton.h
SOURCES += panels/landinggearwidget.cpp \
    panels/headingwidget.cpp \
    panels/flapswidget.cpp \
    panels/chatwidget.cpp \
    panels/autothrottlewidget.cpp \
    panels/altitudewidget.cpp \
    network/servercall.cpp \
    main.cpp \
    glareshieldwidget.cpp \
    widgets/xlabel.cpp \
    widgets/xdigit.cpp \
    widgets/gsreadoutwidget.cpp \
    widgets/gsbutton.cpp
OTHER_FILES += resources/butt_on.png \
    resources/butt_off.png \
    resources/bullet_picture.png \
    resources/bullet_black.png \
    resources/bullet_arrow_up.png \
    resources/bullet_arrow_top.png \
    resources/bullet_arrow_down.png \
    resources/bullet_arrow_bottom.png \
    resources/bot.jpg
RESOURCES += resources/icons.qrc
