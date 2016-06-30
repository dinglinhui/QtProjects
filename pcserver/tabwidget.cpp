#include <QtGui>
#include "tabwidget.h"

TabWidget::TabWidget(QWidget *parent) :
    QTabWidget(parent),
    welcomWidget(new WelcomeWidget),
    examinationWidget(new ExaminationWidget),
    communicationWidget(new CommunicationWidget)
{
    this->addTab(welcomWidget, QIcon(":/res/images/home.png"), PCSERVER_WELCOME);
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(removeSubTab(int)));

    this->setCurrentIndex(0);
    this->setTabsClosable(false);
    this->setMovable(true);
    this->setTabBarAutoHide(true);
}

TabWidget::~TabWidget()
{
    if(nullptr != welcomWidget)
        delete welcomWidget, welcomWidget = nullptr;
    if(nullptr != examinationWidget)
        delete examinationWidget, examinationWidget = nullptr;
    if(nullptr != communicationWidget)
        delete communicationWidget, communicationWidget = nullptr;
}

void TabWidget::addConnManageTab()
{
    this->addTab(communicationWidget, QIcon(":/res/images/256/virus.png"), COMMUNICATION_MANAGE);
    this->setCurrentWidget(communicationWidget);
}

void TabWidget::addExamManageTab()
{
    this->addTab(examinationWidget, QIcon(":/res/images/256/book.png"), EXAMINATION_MANAGE);
    this->setCurrentWidget(examinationWidget);
}

void TabWidget::onSocketConnect(const int socketDescriptor, const QString & ip, const quint16 port)
{
    qDebug() << "socket connect" << socketDescriptor << " " << ip << " " << port << endl;
    QString channel = QStringLiteral("%1(%2)").arg(ip).arg(socketDescriptor);
    if (!communicationWidget->getCommunicationTree()->searchItems(channel))
//        communicationWidget->getCommunicationTree()->insertItems(channel, port, LINKINFO_CONNECTED);
        communicationWidget->getCommunicationTree()->insertItems(socketDescriptor, ip, port, LINKINFO_CONNECTED);
    else
        communicationWidget->getCommunicationTree()->changeItems(channel, LINKINFO_CONNECTED);
}

void TabWidget::onSocketDisConnect(const int socketDescriptor, const QString & ip, const quint16 port)
{
    qDebug() << "socket disconnect" << socketDescriptor << " " << ip << " " << port << endl;
    QString channel = QStringLiteral("%1(%2)").arg(ip).arg(socketDescriptor);
    communicationWidget->getCommunicationTree()->changeItems(channel, LINKINFO_DISCONNECTED);
}

void TabWidget::removeSubTab(int index)
{
    this->removeTab(index);
}
