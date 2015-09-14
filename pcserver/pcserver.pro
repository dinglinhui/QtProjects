TARGET      = pcserver
TEMPLATE    = app
INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD
QT          += core \
            gui \
            xml \
            network \
            sql \
            printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += C++11
CONFIG   -= app_bundle

SOURCES += \
    borderlayout.cpp \
    dbmysql.cpp \
    freezetableview.cpp \
    main.cpp \
    mainwindow.cpp \
    pcserver.cpp \
    tcpserver.cpp \
    tcpsocket.cpp \
    threadhandle.cpp \
    transmittree.cpp \
    utils.cpp \
    xmlparser.cpp \
    analyzedock.cpp \
    logdock.cpp \
    transmittable.cpp \
    tabwidget.cpp \
    proxymodel.cpp \
    transmitwidget.cpp \
    welcomewidget.cpp \
    configdialog.cpp

HEADERS += \
    borderlayout.h \
    dbmysql.h \
    freezetableview.h \
    itemdelegate.h \
    mainwindow.h \
    pcdefs.h \
    pcserver.h \
    tcpserver.h \
    tcpsocket.h \
    threadhandle.h \
    transmittree.h \
    utils.h \
    xmlparser.h \
    analyzedock.h \
    logdock.h \
    transmittable.h \
    tabwidget.h \
    proxymodel.h \
    transmitwidget.h \
    welcomewidget.h \
    configdialog.h

RESOURCES += pcserver.qrc

include($$PWD/3rdparty/qtxlsx/src/xlsx/qtxlsx.pri)
unix:include($$PWD/3rdparty/eventdispatcher_libev/eventdispatcher_libev.pri)
