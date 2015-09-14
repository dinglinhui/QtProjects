TEMPLATE = app
TARGET = pcclient
QT  += core \
    widgets \
    gui \
    xml \
    network \
    printsupport

include(3rdparty/qtxlsx/src/xlsx/qtxlsx.pri)

HEADERS += configdialog.h \
    pages.h \
    commpkttree.h \
    rtdbtab.h \
    rtdbtree.h \
    iec61850tree.h \
    iec103tree.h \
    freezetableview.h \
    iec61850tab.h \
    borderlayout.h \
    pctab.h \
    iec103tab.h \
    itemdelegate.h \
    rtdbeditdlg.h \
    commcfgdlg.h \
    commpkttab.h \
    pcdefs.h \
    pcmodel.h \
    pcwidget.h \
    uddthread.h \
    tablemodel.h \
    welcometab.h \
    xmlparser.h \
    pcclient.h \
    transmittab.h \
    transmittree.h \
    transmitthread.h
SOURCES += configdialog.cpp \
    pages.cpp \
    commpkttree.cpp \
    rtdbtab.cpp \
    rtdbtree.cpp \
    iec61850tree.cpp \
    iec103tree.cpp \
    freezetableview.cpp \
    iec61850tab.cpp \
    borderlayout.cpp \
    pctab.cpp \
    iec103tab.cpp \
    rtdbeditdlg.cpp \
    commpkttab.cpp \
    pcmodel.cpp \
    welcometab.cpp \
    pcwidget.cpp \
    tablemodel.cpp \
    uddthread.cpp \
    xmlparser.cpp \
    commcfgdlg.cpp \
    pcclient.cpp \
    main.cpp \
    transmittab.cpp \
    transmittree.cpp \
    transmitthread.cpp
FORMS += 
RESOURCES += pcclient.qrc
RC_FILE += pcclient.rc
#win32:CONFIG += console
