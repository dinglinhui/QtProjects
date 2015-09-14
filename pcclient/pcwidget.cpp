#include <QtGui>
#include "pcwidget.h"
#include "pcdefs.h"

PCWidget::PCWidget(QWidget *parent) :
    QTabWidget(parent),
    m_pWelcomTab(new WelcomeTab),//欢迎tab
    m_pRtdbTab(new RtdbTab),//实时库tab
    m_pCommpktTab(new CommPktTab),//通信报文tab
    m_pTransmitTab(new TransmitTab)//转发表tab
{
    this->addTab(m_pWelcomTab, QIcon(":/system/images/home.png"), PCCLIENT_WELCOME);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(removeSubTab(int)));

    connect(m_pRtdbTab, SIGNAL(enableRefreshSingleSignal()), parent, SLOT(enableRefreshSingleAction()));
    connect(m_pRtdbTab, SIGNAL(enableSaveDataSignal()), parent, SLOT(enableSaveDataAction()));
    connect(m_pRtdbTab, SIGNAL(refreshAllRtdbSignal()), parent, SLOT(refreshAllRtdb()));
    connect(m_pRtdbTab, SIGNAL(refreshSingleRtdbSignal()), parent, SLOT(refreshSingleRtdb()));
    connect(m_pRtdbTab, SIGNAL(saveRtdbDataSignal(QMap<int, QStringList> &)), parent, SLOT(saveRtdbData(QMap<int, QStringList> &)));
    connect(m_pRtdbTab->rtdbTree, SIGNAL(treeClicked(const QModelIndex &)), parent, SLOT(onRtdbTreeClicked(const QModelIndex &)));

    connect(m_pCommpktTab, SIGNAL(analyzePacketSignal(const QStringList &)), parent, SLOT(analyzePacket(const QStringList &)));
    connect(m_pCommpktTab->commpktTree, SIGNAL(treeClicked(const QModelIndex &)), parent, SLOT(onCommPktTreeClicked(const QModelIndex &)));

    connect(m_pTransmitTab, SIGNAL(endSignl()), parent, SLOT(onEndRequest()));
    connect(m_pTransmitTab, SIGNAL(callSignl()), parent, SLOT(onCallTransmit()));
    connect(m_pTransmitTab, SIGNAL(saveSignl(const QString & )), parent, SLOT(onSaveProcesser(const QString & )));
    connect(m_pTransmitTab->transmitTree, SIGNAL(treeClicked(const QModelIndex &)), parent, SLOT(onTransmitTreeClicked(const QModelIndex &)));
    //IEC103功能tab
    //iec103Tab = new IEC103Tab;
    //IEC61850功能tab
    //iec61850Tab = new IEC61850Tab;

    this->setCurrentIndex(TAB_WELCOME);
    this->setTabsClosable(true);
}

void PCWidget::addRtdbTab()
{
    this->addTab(m_pRtdbTab, QIcon(":/system/images/256/slot_machine.png"), RTDB_DATA);
    this->setCurrentWidget(m_pRtdbTab);
}

void PCWidget::addCommPktTab()
{
    this->addTab(m_pCommpktTab, QIcon(":/system/images/256/binoculars.png"), COMMUNICATION_PACKET);
    this->setCurrentWidget(m_pCommpktTab);
}

void PCWidget::addTransmitTab()
{
    this->addTab(m_pTransmitTab, QIcon(":/system/images/256/virus.png"), TRANSMIT_TABLE);
    this->setCurrentWidget(m_pTransmitTab);
}

void PCWidget::addIEC103Tab()
{
    //this->addTab(iec103Tab, QIcon(":/system/images/256/shield.png"), IEC103_FUNCTION);
    //this->setCurrentWidget(iec103Tab);
}

void PCWidget::addIEC61850Tab()
{
    //this->addTab(iec61850Tab, QIcon(":/system/images/256/world.png"), IEC61850_FUNCTION);
    //this->setCurrentWidget(iec61850Tab);
}

void PCWidget::closeTransmitTab()
{

}

void PCWidget::removeSubTab(int index)
{
    this->removeTab(index);
}
