TARGET      = pcserver
TEMPLATE    = app
INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD
QT          += core \
            gui \
            xml \
            network \
            sql \
            printsupport \
            opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += C++11
CONFIG   -= app_bundle

SOURCES += \
    borderlayout.cpp \
    freezetableview.cpp \
    main.cpp \
    mainwindow.cpp \
    pcserver.cpp \
    tcpserver.cpp \
    tcpsocket.cpp \
    threadhandle.cpp \
    utils.cpp \
    xmlparser.cpp \
    analyzedock.cpp \
    logdock.cpp \
    tabwidget.cpp \
    proxymodel.cpp \
    welcomewidget.cpp \
    configdialog.cpp \
    networkinformation.cpp \
    logindialog.cpp \
    mainwidget.cpp \
    communicationwidget.cpp \
    communicationtable.cpp \
    communicationtree.cpp \
    examinationtable.cpp \
    examinationtree.cpp \
    examinationwidget.cpp \
    sqltablemodel.cpp \
    comboboxitem.cpp \
    nofocusframedelegate.cpp

HEADERS += \
    borderlayout.h \
    freezetableview.h \
    itemdelegate.h \
    mainwindow.h \
    pcdefs.h \
    pcserver.h \
    tcpserver.h \
    tcpsocket.h \
    threadhandle.h \
    utils.h \
    xmlparser.h \
    analyzedock.h \
    logdock.h \
    tabwidget.h \
    proxymodel.h \
    welcomewidget.h \
    configdialog.h \
    networkinformation.h \
    logindialog.h \
    mainwidget.h \
    communicationwidget.h \
    communicationtable.h \
    communicationtree.h \
    examinationtable.h \
    examinationtree.h \
    examinationwidget.h \
    sqltablemodel.h \
    comboboxitem.h \
    nofocusframedelegate.h

RESOURCES += pcserver.qrc

#include($$PWD/3rdparty/qtxlsx/src/xlsx/qtxlsx.pri)
#unix:include($$PWD/3rdparty/eventdispatcher_libev/eventdispatcher_libev.pri)
