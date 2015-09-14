#include <QtGui>
#include "tabwidget.h"

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent),
//    welcomWidget(new WelcomeWidget),
    transmitWidget(new TransmitWidget)
{
//    this->addTab(welcomWidget, QIcon(":/res/images/home.png"), PCSERVER_WELCOME);
//    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(removeSubTab(int)));

    this->addTab(transmitWidget, QIcon(":/res/images/256/virus.png"), TRANSMIT_TABLE);

    this->setCurrentIndex(0);
    this->setTabsClosable(false);
    this->setMovable(true);
}

TabWidget::~TabWidget()
{
    if(nullptr != transmitWidget)
        delete transmitWidget, transmitWidget = nullptr;
}

void TabWidget::onSocketConnect(const int socketDescriptor, const QString & ip, const quint16 port)
{
    qDebug() << "socket connect" << socketDescriptor << " " << ip << " " << port << endl;
    QString channel = QStringLiteral("%1(%2)").arg(ip).arg(socketDescriptor);
    if (!transmitWidget->getTransmitTree()->searchItems(channel))
//        transmitWidget->getTransmitTree()->insertItems(channel, port, LINKINFO_CONNECTED);
        transmitWidget->getTransmitTree()->insertItems(socketDescriptor, ip, port, LINKINFO_CONNECTED);
    else
        transmitWidget->getTransmitTree()->changeItems(channel, LINKINFO_CONNECTED);
}

void TabWidget::onSocketDisConnect(const int socketDescriptor, const QString & ip, const quint16 port)
{
    qDebug() << "socket disconnect" << socketDescriptor << " " << ip << " " << port << endl;
    QString channel = QStringLiteral("%1(%2)").arg(ip).arg(socketDescriptor);
    transmitWidget->getTransmitTree()->changeItems(channel, LINKINFO_DISCONNECTED);
}

void TabWidget::removeSubTab(int index)
{
    this->removeTab(index);
}
