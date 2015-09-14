#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H

#include <QTreeView>
#include <QTableView>
#include <QTabWidget>
#include <QItemSelection>
#include "tablemodel.h"
#include "pcmodel.h"
#include "welcometab.h"
#include "rtdbtab.h"
#include "commpkttab.h"
#include "transmittab.h"
#include "iec61850tab.h"
#include "iec103tab.h"

QT_BEGIN_NAMESPACE
class QSortFilterProxyModel;
class QItemSelectionModel;
class QStandardItemModel;
QT_END_NAMESPACE

class PCWidget: public QTabWidget
{
    Q_OBJECT

public:
    PCWidget(QWidget *parent = 0);

    void addRtdbTab();
    void addCommPktTab();
    void addTransmitTab();
    void addIEC103Tab();
    void addIEC61850Tab();

    void closeTransmitTab();

public slots:
    void removeSubTab(int index);

public:
    WelcomeTab *m_pWelcomTab;
    RtdbTab *m_pRtdbTab;
    CommPktTab *m_pCommpktTab;
    TransmitTab *m_pTransmitTab;
    //IEC103Tab *iec103Tab;
    //IEC61850Tab *iec61850Tab;
};

#endif
