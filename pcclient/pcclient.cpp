#include <QtGui>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>
#include <QProgressDialog>
#include "pcclient.h"
#include "commcfgdlg.h"
#include "xmlparser.h"

PCClient::PCClient() :
    m_pUddThread(new UddThread(this)),
    m_pTransThread(new TransmitThread(this)),
    m_pWidget(new PCWidget(this)),
    m_pAnalyzeDock(new QDockWidget(COMMPKT_PACKET_ANALYZE, this)),
    m_pTableView(new QTableView()),
    m_pModel(new PCModel(this)),
    m_pLogDock(new QDockWidget(COMMPKT_SYSTEM_LOG, this)),
    m_pLogTxt(new QTextEdit()),
    m_pServiceMenu(this->menuBar()->addMenu(MENU_SERVICE)),
    m_pFunctionMenu(this->menuBar()->addMenu(MENU_FUNCTION)),
    m_pInterfaceMenu(this->menuBar()->addMenu(MENU_INTERFACE)),
    m_pHelpMenu(this->menuBar()->addMenu(MENU_HELP)),
    m_pCfgToolBar(this->addToolBar(tr("Config"))),
    m_pRtdbToolBar(this->addToolBar(tr("RTDB"))),
    m_pPacketToolBar(this->addToolBar(tr("Packet"))),
    m_pFunctionToolBar(this->addToolBar(tr("Function"))),
    m_pSystemToolBar(this->addToolBar(tr("System"))),
    m_pCommCfgAct(new QAction(QIcon(":/system/images/256/connect.png"), tr("&Communication Config"), this)),
    m_pCommPktAct(new QAction(QIcon(":/system/images/256/binoculars.png"), tr("&Communication Packet"), this)),
    m_pStartRollAct(new QAction(QIcon(":/system/images/256/checkmark.png"), tr("&Start Rolling"), this)),
    m_pStopRollAct(new QAction(QIcon(":/system/images/256/cancel.png"), tr("&Stop Rolling"), this)),
    m_pTransAct(new QAction(QIcon(":/system/images/256/virus.png"), tr("Transmit"), this)),
    m_pConnTransAct(new QAction(QIcon(":/system/images/256/connect_vertical.png"), tr("Call Transmit"), this)),
    m_pDisconnTransAct(new QAction(QIcon(":/system/images/256/disconnect_vertical.png"), tr("Call Transmit"), this)),
    m_pCallTransAct(new QAction(QIcon(":/system/images/256/reload.png"), tr("Call Transmit"), this)),
    m_pPrintTransAct(new QAction(QIcon(":/system/images/256/print.png"), tr("print Transmit"), this)),
    //m_pIec103Act(new QAction(QIcon(":/system/images/256/shield.png"), tr("&IEC103 Function"), this)),
    //m_pIec61850Act(new QAction(QIcon(":/system/images/256/world.png"), tr("&IEC61850 Function"), this)),
    m_pRtdbAct(new QAction(QIcon(":/system/images/256/slot_machine.png"), tr("&RTDB"), this)),
    m_pRefreshAllAct(new QAction(QIcon(":/system/images/256/refresh.png"), tr("&Refresh All RTDB"), this)),
    m_pRefreshSingleAct(new QAction(QIcon(":/system/images/256/down.png"), tr("&Refresh single RTDB"), this)),
    m_pSaveRtdbAct(new QAction(QIcon(":/system/images/256/diskette.png"), tr("&Save RTDB"), this)),
    m_pQuitAct(new QAction(QIcon(":/system/images/256/close.png"), tr("&Quit System"), this)),
    m_pAboutAct(new QAction(QIcon(":/system/images/256/info.png"), tr("&About PCClient"), this)),
    masterFlag(false),
    m_bRequestEnd(false)
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("PCClientClass"));

    this->setWindowModality(Qt::WindowModal);
    this->setMinimumSize(800, 500);
    this->resize(QApplication::desktop()->width()/2, QApplication::desktop()->height()/2);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setWindowIcon(QIcon(":/system/images/PCClient.png"));
    this->setWindowTitle(tr("PCClient"));
    this->setAutoFillBackground(true);
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setCentralWidget(m_pWidget);
    this->drawWindows();
}

PCClient::~PCClient()
{

}

void PCClient::closeEvent(QCloseEvent *event)
{
    switch (QMessageBox::information(this, QUIT_TITLE, QUIT_TEXT, CONFIRM, CANCEL, 0, 1))
    {
    case 0:
    {
        if (m_pUddThread->isRunning())
        {
            appendToLog("stop udd thread!");
            qDebug() << "stop udd thread!";
            m_pUddThread->stop();
            m_pUddThread->quit();
            m_pUddThread->wait();
            delete m_pUddThread;
        }

        if (m_pTransThread->isRunning())
        {
            appendToLog("stop transmit thread!");
            qDebug() << "stop transmit thread!";
            m_pTransThread->stop();
            m_pTransThread->quit();
            m_pTransThread->wait();
            delete m_pTransThread;
        }

        event->accept();
        break;
    }
    case 1:
    default:
    {
        event->ignore();
        break;
    }
    }
}

void PCClient::initUddThread(SERVER_INFO *pServer)
{
    m_pUddThread->closeSocket();
    m_pUddThread->initServerInfo(pServer);
}

void PCClient::initTransmitThread(SERVER_INFO *pServer)
{
    m_pTransThread->disconnectSocket();
    m_pTransThread->initServerInfo(pServer);
}

void PCClient::startUddThread()
{
    connect(m_pUddThread, SIGNAL(finished()), m_pUddThread, SLOT(deleteLater()));
    m_pUddThread->start();
    //
    qDebug() << "start udd thread!";
    appendToLog(QString("start socket thread!"));
}

void PCClient::startTransmitThread()
{
    connect(m_pTransThread, SIGNAL(finished()), m_pTransThread, SLOT(deleteLater()));
    m_pTransThread->start();
    //
    qDebug() << "start transmit thread!";
    appendToLog(QString("start transmit thread!"));
}

void PCClient::onCommCfgDlg()
{
    QString fileName = PCCLIENT_HOME.append("/pcclient.xml");
    appendToLog(fileName);
    CommCfgDlg* ccd = new CommCfgDlg(fileName, this);
    if (ccd->exec() == QDialog::Accepted)
    {
        SERVER_INFO server;
        server.ip = ccd->getGeneralTab()->getIP();
        server.srcPort = ccd->getGeneralTab()->getSrcPort();
        server.destPort = ccd->getGeneralTab()->getDestPort();
        server.transPort = ccd->getGeneralTab()->getTransPort();
        server.transEnable = (ccd->getGeneralTab()->isTransEnable()?QString("1"):QString("0"));
        appendToLog(server.ip + " " + server.srcPort + " " + server.destPort + " " + server.transPort + " " + server.transEnable);

        XmlParser parser;
        if (!parser.writeXml(fileName, XML_ELEMENT_SERVERINFO, &server))
        {
            qDebug() << "writeXml failure!" << endl;
            appendToLog(QString("writeXml failure!"));
        }

        ccd->close();

        this->initUddThread(&server);
        if (!m_pUddThread->isRunning())
        {
            this->startUddThread();
        }

        m_pRtdbAct->setEnabled(true);
        m_pCommPktAct->setEnabled(true);
        m_pWidget->addRtdbTab();
        m_pWidget->addCommPktTab();

        //如果启用转发表功能
        if(ccd->getGeneralTab()->isTransEnable())
        {
            m_pWidget->addTransmitTab();
            if (!m_pTransThread->isRunning())
            {
                this->startTransmitThread();
                this->initTransmitThread(&server);
                m_pTransAct->setEnabled(true);
                m_pConnTransAct->setEnabled(true);
                m_pDisconnTransAct->setEnabled(false);
                m_pCallTransAct->setEnabled(false);
                m_pPrintTransAct->setEnabled(true);
            }
        }

        m_pWidget->setCurrentWidget(m_pWidget->m_pRtdbTab);
    }
    else
    {
        ccd->close();
    }
}

void PCClient::onCommPktTab()
{
    m_pWidget->addCommPktTab();
}

void PCClient::onRtdbDataTab()
{
    m_pWidget->addRtdbTab();
}

void PCClient::onTransmitTab()
{
    m_pWidget->addTransmitTab();
}

void PCClient::onIEC103Tab()
{
    m_pWidget->addIEC103Tab();
}

void PCClient::onIEC61850Tab()
{
    m_pWidget->addIEC61850Tab();
}

void PCClient::connectRequest()
{
    m_pConnTransAct->setEnabled(true);
    m_pDisconnTransAct->setEnabled(false);
    m_pCallTransAct->setEnabled(false);
}

void PCClient::disconnectRequest()
{
    m_pConnTransAct->setEnabled(false);
    m_pDisconnTransAct->setEnabled(true);
    m_pCallTransAct->setEnabled(true);
}

void PCClient::enableRefreshSingleAction()
{
    m_pRefreshSingleAct->setEnabled(true);
}

void PCClient::enableSaveDataAction()
{
    m_pSaveRtdbAct->setEnabled(true);
}

void PCClient::startRolling()
{
    m_pWidget->m_pCommpktTab->setRolling(true);
    m_pStartRollAct->setEnabled(false);
    m_pStopRollAct->setEnabled(true);
    appendToLog("start rolling!");
}

void PCClient::stopRolling()
{
    m_pWidget->m_pCommpktTab->setRolling(false);
    m_pStartRollAct->setEnabled(true);
    m_pStopRollAct->setEnabled(false);
    appendToLog("stop rolling!");
}

void PCClient::refreshAllRtdb()
{
    QModelIndex index = m_pWidget->m_pRtdbTab->rtdbTree->currentIndex();
    if (index.row() != -1)
    {
        QByteArray buffer;
        buffer.resize(HEADNUMBER);
        m_pWidget->m_pRtdbTab->clearModel(index.row());
        switchRequest(buffer, TABLE_MX + index.row());
        appendToLog(QString("refresh rtdb %1!").arg(index.row()));
        onSaveProcesser(QStringLiteral("正在召唤中..."));
    }
    else
    {
        qDebug() << index.row();
        appendToLog("refreshAllRtdb rtdbTree currentIndex -1");
    }

    m_pSaveRtdbAct->setEnabled(false);
}

void PCClient::refreshSingleRtdb()
{
    QStringList list;
    if (m_pWidget->m_pRtdbTab->getCurrentRow(list) != -1)
    {
        QModelIndex index = m_pWidget->m_pRtdbTab->rtdbTree->currentIndex();
        if (index.row() != -1)
        {
            int sAddr = list.at(TABLE_RTDBINFO_SADDR).toInt();
            QByteArray buffer;
            buffer.resize(HEADNUMBER);
            buffer.insert(HEADNUMBER, (const char *) &sAddr, 4);
            switchRequest(buffer, index.row() + RECORD_MX);
            appendToLog(QString("refresh rtdb %1 sAddr %2!").arg(index.row()).arg(sAddr));
        }
        else
        {
            qDebug() << index.row();
            appendToLog("refreshSingleRtdb rtdbTree currentIndex -1");
        }
    }
    else
    {
        qDebug() << m_pWidget->m_pRtdbTab->getCurrentRow(list);
        appendToLog("refreshSingleRtdb rtdbTab currentRow -1");
    }
}

void PCClient::saveRtdbData()
{
    saveRtdbData(m_pWidget->m_pRtdbTab->getEditMap());
    m_pWidget->m_pRtdbTab->clearEditFlag(); //先清除编辑标志，再清除Map
    m_pWidget->m_pRtdbTab->clearEditMap();
    m_pSaveRtdbAct->setEnabled(false);
}

void PCClient::saveRtdbData(QMap<int, QStringList> &map)
{
    //此处限制只处理MX、ST、CO点表的数据修改
    QModelIndex index = m_pWidget->m_pRtdbTab->rtdbTree->currentIndex();
    if ((index.row() < RTDB_SP) || (index.row() >= RTDB_MX))
    {
        char tmp = 0x00;
        int nSaddr = 0, nIntValue = 0, nTotalNum = 0;
        double fDoubleValue = 0.0;

        QString sAddr;
        QString dataType;
        QString dataValue;
        QByteArray buffer;
        buffer.resize(HEADNUMBER);

        QMutableMapIterator<int, QStringList> it(map);
        while (it.hasNext())
        {
            it.next();
            sAddr = it.value().at(TABLE_RTDBINFO_SADDR);
            dataType = it.value().at(TABLE_RTDBINFO_DATATYPE);
            dataValue = it.value().at(TABLE_RTDBINFO_DATAVALUE);

            nSaddr = sAddr.toInt();
            buffer.insert(HEADNUMBER + nTotalNum, (const char *) &nSaddr, 4);

            if (dataType == QString(DATATYPE_INT)) //整形
            {
                nIntValue = dataValue.toInt();
                tmp = 0x00;
                buffer.insert(HEADNUMBER + nTotalNum + 4, (const char *) &tmp, 1);
                buffer.insert(HEADNUMBER + nTotalNum + 5, (const char *) &nIntValue, 4);

                nTotalNum += 9;
            }
            else if (dataType == QString(DATATYPE_FLOAT)) //浮点型
            {
                fDoubleValue = dataValue.toDouble();
                tmp = 0x01;
                buffer.insert(HEADNUMBER + nTotalNum + 4, (const char *) &tmp, 1);
                buffer.insert(HEADNUMBER + nTotalNum + 5, (const char *) &fDoubleValue, 8);

                nTotalNum += 13;
            }
            else
            {
                qDebug() << "dataType" << dataType << "error";
                appendToLog(QString("saveRtdbData dataType %1 error").arg(dataType));
            }
        }

        if (map.size() > 0)
        {
            switchRequest(buffer, index.row() + TABLE_MX_RSP, nTotalNum, map.size());
            appendToLog(QString("save rtdb %1 num %2!").arg(index.row()).arg(map.size()));
        }
    }
    m_pSaveRtdbAct->setEnabled(false);
}

void PCClient::switchStation(const QByteArray &buffer)
{
    int flag = 0;
    if (buffer.data()[0] == 0X68) {
        flag = (unsigned char) buffer.data()[5];
        switch (flag) {
        case REPORT_MESSAGE:
            m_pWidget->m_pCommpktTab->displayReport(buffer);
            break;
        case ENDFLAG_RSP:
//            qDebug() << "end flag";
            m_bRequestEnd = true;
            break;
        case TABLE_MX_RSP:
        case TABLE_ST_RSP:
        case TABLE_CO_RSP:
        case TABLE_SP_RSP:
        case TABLE_SG_RSP:
        case TABLE_SE_RSP:
            m_pWidget->m_pRtdbTab->displayRtdbTable(buffer, flag - TABLE_MX_RSP);
            break;
        case RECORD_MX_RSP:
        case RECORD_ST_RSP:
        case RECORD_CO_RSP:
        case RECORD_SP_RSP:
        case RECORD_SG_RSP:
        case RECORD_SE_RSP:
            m_pWidget->m_pRtdbTab->updateRtdbTable(buffer, flag - RECORD_MX_RSP);
            break;
        case TRANSMIT_CHNL_A_RSP:
        case TRANSMIT_CHNL_S_RSP:
        case TRANSMIT_AI_RSP:
        case TRANSMIT_COS_RSP:
        case TRANSMIT_DO_RSP:
        case TRANSMIT_END_RSP:
        case SOE_BUFFER_CHNL_RSP:
        case SOE_BUFFER_DATA_RSP:
            m_pWidget->m_pTransmitTab->displayTransmitTable(buffer, flag);
            break;
        default:
            break;
        }
    }
}

void PCClient::switchRequest(QByteArray &buffer, int nRequestType, int nDataNum, int nRecordConut)
{
    switch (nRequestType)
    {
    case SEND_RPT_START:
    case SEND_RPT_STOP:
    case TABLE_MX:
    case TABLE_ST:
    case TABLE_CO:
    case TABLE_SP:
    case TABLE_SG:
    case TABLE_SE:
        makeRequestReport(buffer, nRequestType);
        m_pUddThread->sendToQueue(buffer);
        break;
    case TRANSMIT_CHNL_A:
    case TRANSMIT_CHNL_S:
    case TRANSMIT_AI:
    case TRANSMIT_COS:
    case TRANSMIT_DO:
    case SOE_BUFFER_CHNL:
    case SOE_BUFFER_DATA:
        makeRequestTransmit(buffer, nRequestType, nDataNum);
        m_pTransThread->sendToQueue(buffer);
        break;
    case RECORD_MX:
    case RECORD_ST:
    case RECORD_CO:
    case RECORD_SP:
    case RECORD_SG:
    case RECORD_SE:
        makeRecordAskBuffer(buffer, nRequestType, 1);
        m_pUddThread->sendToQueue(buffer);
        break;
    case TABLE_MX_RSP:
    case TABLE_ST_RSP:
    case TABLE_CO_RSP:
    case TABLE_SP_RSP:
    case TABLE_SG_RSP:
    case TABLE_SE_RSP:
        makeRtdbSendReport(buffer, nRequestType, nDataNum, nRecordConut);
        m_pUddThread->sendToQueue(buffer);
        break;
    default:
        break;
    }
}

void PCClient::makeRequestReport(QByteArray &buffer, int nRequestType)
{
    int nPos = 0;
    buffer[nPos++] = 0X68;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = (char) nRequestType;
    buffer[nPos++] = 0X01;
    buffer[23] = 0X00;
    buffer[24] = 0X00;
    buffer[25] = 0X00;
}

void PCClient::makeRequestTransmit(QByteArray &buffer, int nRequestType, int nChannel)
{
    int nPos = 0;
    buffer[nPos++] = 0X68;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = (char) nRequestType;
    buffer[nPos++] = 0X01;
    buffer[23] = 0X00;
    buffer[24] = 0X00;
    buffer[25] = (char) nChannel;
}

void PCClient::makeRecordAskBuffer(QByteArray &buffer, int nReportType, int nRecordCount)
{
    int nTotalNum = 4 * nRecordCount;
    int nPos = 0;
    buffer[nPos++] = 0X68;
    buffer[nPos++] = (nTotalNum & 0X0000FF00) >> 8;
    buffer[nPos++] = (nTotalNum & 0X000000FF);
    buffer[nPos++] = 0X00;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = (char) nReportType;
    buffer[nPos++] = 0X01;
    buffer[23] = 0X00;
    buffer[24] = (char) nRecordCount;
    buffer[25] = 0X00;
}

void PCClient::makeRtdbSendReport(QByteArray &buffer, int nReportType, int nDataNum, int nRecordConut)
{
    int nPos = 0;
    buffer[nPos++] = 0X68;
    buffer[nPos++] = (char) ((nDataNum & 0X0000FF00) >> 8);
    buffer[nPos++] = (char) (nDataNum & 0X000000FF);
    buffer[nPos++] = 0X00;
    buffer[nPos++] = 0X00;
    buffer[nPos++] = (char) nReportType;
    buffer[23] = 0X00;
    buffer[24] = (char) nRecordConut;
    buffer[25] = 0X00;
}

void PCClient::onRtdbTreeClicked(const QModelIndex & index)
{
    m_pRefreshAllAct->setEnabled(true);
    m_pRefreshSingleAct->setEnabled(false);
    m_pSaveRtdbAct->setEnabled(false);

    m_pWidget->m_pRtdbTab->changeModel(index.row());
}

void PCClient::onCommPktTreeClicked(const QModelIndex & index)
{
    if (!masterFlag)
    {
        m_pStartRollAct->setEnabled(true);
        m_pStopRollAct->setEnabled(false);
        masterFlag = true;
    }

    m_pWidget->m_pCommpktTab->masterFilterChanged(m_pWidget->m_pCommpktTab->commpktTree->getCurrentItemName());
}

void PCClient::onTransmitTreeClicked(const QModelIndex & index)
{
//    qDebug() << index.parent().parent().row() << index.parent().row() << index.row();
    if((index.parent().parent().row() == -1)&&(index.parent().row() == -1))
    {
        if(index.row() <= TRANSINFO_TRANSMIT)//转发表
        {
            m_pWidget->m_pTransmitTab->changeModel(index.row(), 0, TRANSMIT_CHNL_S);
        }
        else//SOE缓存
        {
            m_pWidget->m_pTransmitTab->changeModel(index.row(), 0, SOE_BUFFER_CHNL);
        }
    }
    else if(index.parent().parent().row() == -1)
    {
        if(index.parent().row() == TRANSINFO_TRANSMIT)//转发表
        {
            m_pWidget->m_pTransmitTab->changeModel(index.row(), 0, TRANSMIT_CHNL_S);
        }
        else//SOE缓存
        {
            m_pWidget->m_pTransmitTab->changeModel(index.row(), 0, SOE_BUFFER_CHNL);
        }
    }
    else if(index.parent().parent().row() == TRANSINFO_TRANSMIT)//转发表
    {
        m_pWidget->m_pTransmitTab->changeModel(index.parent().row(), 0, TRANSMIT_AI+index.row());
    }
    else// if(index.parent().parent().row() == TRANSINFO_SOEBUFFER)//SOE缓存
    {
        m_pWidget->m_pTransmitTab->changeModel(index.parent().row(), index.row(), SOE_BUFFER_CHNL);
    }
}

void PCClient::analyzePacket(const QStringList &list)
{
    m_pAnalyzeDock->setVisible(true);
    //
    m_pModel->removeColumn(0);
    m_pModel->insertColumn(0);
    m_pModel->setData(m_pModel->index(TABLE_COMMPKT_MASTER, 0), list.at(TABLE_COMMPKT_MASTER));
    m_pModel->setData(m_pModel->index(TABLE_COMMPKT_SEND_RECV, 0), list.at(TABLE_COMMPKT_SEND_RECV));
    m_pModel->setData(m_pModel->index(TABLE_COMMPKT_TIME, 0), list.at(TABLE_COMMPKT_TIME));
    m_pModel->setData(m_pModel->index(TABLE_COMMPKT_PACKET, 0), list.at(TABLE_COMMPKT_PACKET));
    m_pModel->setData(m_pModel->index(TABLE_COMMPKT_PACKET_ANALYZE, 0), QString(tr("分析功能正在开发过程中！")));
}

void PCClient::onConnTransmit()
{
    m_pTransThread->connectSocket();
    m_pConnTransAct->setEnabled(false);
    m_pDisconnTransAct->setEnabled(true);
}

void PCClient::onDisconnTransmit()
{
    m_pTransThread->disconnectSocket();
    m_pConnTransAct->setEnabled(true);
    m_pDisconnTransAct->setEnabled(false);
}

void PCClient::onCallTransmit()
{
    QByteArray buffer;
    buffer.resize(HEADNUMBER);
    QModelIndex index = m_pWidget->m_pTransmitTab->transmitTree->currentIndex();
    if((index.parent().parent().row() == -1)&&(index.parent().row() == -1))
    {
        if(index.row() <= TRANSINFO_TRANSMIT)//转发表
        {
            m_pWidget->m_pTransmitTab->transmitTree->clearItems(TRANSINFO_TRANSMIT);
            switchRequest(buffer, TRANSMIT_CHNL_A, index.row());
        }
        else//SOE缓存
        {
            m_pWidget->m_pTransmitTab->transmitTree->clearItems(TRANSINFO_SOEBUFFER);
            switchRequest(buffer, SOE_BUFFER_CHNL, index.row());
        }
    }
    else if(index.parent().parent().row() == -1)
    {
        if(index.parent().row() == TRANSINFO_TRANSMIT)//转发表
        {
            m_pWidget->m_pTransmitTab->clearModel(index.row(), 0, TRANSMIT_CHNL_S);//清通道index.row()下所有数据
            switchRequest(buffer, TRANSMIT_CHNL_S, index.row());
        }
        else//SOE缓存
        {
            //只允许召唤具体一台装置的SOE缓存
            //清第一台装置的SOE记录缓存
            //召唤通道index.row()下的第一台装置的SOE缓存
            unsigned char chnlIed = index.row()<<4;

            m_pWidget->m_pTransmitTab->clearModel(index.row(), 0, SOE_BUFFER_DATA);//清通道index.row()下所有数据
            switchRequest(buffer, SOE_BUFFER_DATA, chnlIed);
        }
    }
    else if(index.parent().parent().row() == TRANSINFO_TRANSMIT)//转发表
    {
        m_pWidget->m_pTransmitTab->clearModel(index.parent().row(), 0, index.row()+TRANSMIT_AI );//清通道index.row()下所有数据
        switchRequest(buffer, TRANSMIT_AI + index.row(), index.parent().row());
    }
    else// if(index.parent().parent().row() == TRANSINFO_SOEBUFFER)//SOE缓存
    {
        //召唤通道index.parent().row()下的第index.row()台装置的SOE缓存
        unsigned char chnlIed = index.parent().row()<<4;
        chnlIed += index.row();

        m_pWidget->m_pTransmitTab->clearModel(index.parent().row(), index.row(), SOE_BUFFER_DATA);//清通道index.row()下所有数据
        switchRequest(buffer, SOE_BUFFER_DATA, chnlIed);
    }

    onSaveProcesser(QStringLiteral("正在召唤中..."));
}

void PCClient::onPrintTransmit()
{
    m_pWidget->m_pTransmitTab->printTransmit();
}

void PCClient::onEndRequest()
{
    m_bRequestEnd = true;
}

void PCClient::onSaveProcesser(const QString & info)
{
    QProgressDialog process(this);
    process.setLabelText(info);
    process.setRange(0, 50000);
    process.setModal(true);
    process.setCancelButtonText(QStringLiteral("取消"));
    for (int i = 0; i < 50000; i++)
    {
        for (int j = 0; j < 20000; j++)
            ;
        process.setValue(i);
        if (process.wasCanceled())
            break;

        if (m_bRequestEnd)
        {
            break;
        }
    }
    m_bRequestEnd = false;
}

void PCClient::appendToLog(const QString &str)
{
    QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz"); //设置显示格式
    m_pLogTxt->append(timeStr + " " + str);
}

void PCClient::onAbout()
{
    QMessageBox::about(this, PCCLIENT_ABOUT, PCCLIENT_CONTEXT);
}

void PCClient::drawWindows()
{
    //通信配置
    m_pCommCfgAct->setText(COMMUNICATION_CONFIG);
    m_pCommCfgAct->setStatusTip(COMMUNICATION_CONFIG);
    connect(m_pCommCfgAct, SIGNAL(triggered()), this, SLOT(onCommCfgDlg()));
    //通信报文
    m_pCommPktAct->setText(COMMUNICATION_PACKET);
    m_pCommPktAct->setStatusTip(COMMUNICATION_PACKET);
    m_pCommPktAct->setEnabled(false);
    connect(m_pCommPktAct, SIGNAL(triggered()), this, SLOT(onCommPktTab()));
    //转发表功能
    m_pTransAct->setText(TRANSMIT_FUNCTION);
    m_pTransAct->setStatusTip(TRANSMIT_FUNCTION);
    m_pTransAct->setEnabled(false);
    connect(m_pTransAct, SIGNAL(triggered()), this, SLOT(onTransmitTab()));

    m_pConnTransAct->setText(TRANSMIT_CONNECT);
    m_pConnTransAct->setStatusTip(TRANSMIT_CONNECT);
    m_pConnTransAct->setEnabled(false);
    connect(m_pConnTransAct, SIGNAL(triggered()), this, SLOT(onConnTransmit()));

    m_pDisconnTransAct->setText(TRANSMIT_DISCONNECT);
    m_pDisconnTransAct->setStatusTip(TRANSMIT_DISCONNECT);
    m_pDisconnTransAct->setEnabled(false);
    connect(m_pDisconnTransAct, SIGNAL(triggered()), this, SLOT(onDisconnTransmit()));

    m_pCallTransAct->setText(TRANSMIT_CALL);
    m_pCallTransAct->setStatusTip(TRANSMIT_CALL);
    m_pCallTransAct->setEnabled(false);
    connect(m_pCallTransAct, SIGNAL(triggered()), this, SLOT(onCallTransmit()));

    m_pPrintTransAct->setText(TRANSMIT_PRINT);
    m_pPrintTransAct->setStatusTip(TRANSMIT_PRINT);
    m_pPrintTransAct->setEnabled(false);
    connect(m_pPrintTransAct, SIGNAL(triggered()), this, SLOT(onPrintTransmit()));
    //103功能
    //m_pIec103Act->setText(IEC103_FUNCTION);
    //m_pIec103Act->setStatusTip(IEC103_FUNCTION);
    //connect(m_pIec103Act, SIGNAL(triggered()), this, SLOT(onIEC103Tab()));
    //61850功能
    //m_pIec61850Act->setText(IEC61850_FUNCTION);
    //m_pIec61850Act->setStatusTip(IEC61850_FUNCTION);
    //connect(m_pIec61850Act, SIGNAL(triggered()), this, SLOT(onIEC61850Tab()));
    //启动报文滚动
    m_pStartRollAct->setText(ROLLING_START);
    m_pStartRollAct->setStatusTip(ROLLING_START);
    m_pStartRollAct->setEnabled(false);
    connect(m_pStartRollAct, SIGNAL(triggered()), this, SLOT(startRolling()));
    //停止报文滚动
    m_pStopRollAct->setText(ROLLING_STOP);
    m_pStopRollAct->setStatusTip(ROLLING_STOP);
    m_pStopRollAct->setEnabled(false);
    connect(m_pStopRollAct, SIGNAL(triggered()), this, SLOT(stopRolling()));
    //实时库
    m_pRtdbAct->setText(RTDB_DATA);
    m_pRtdbAct->setStatusTip(RTDB_DATA);
    m_pRtdbAct->setEnabled(false);
    connect(m_pRtdbAct, SIGNAL(triggered()), this, SLOT(onRtdbDataTab()));
    //刷新全表
    m_pRefreshAllAct->setText(RTDB_REFRESH_ALL);
    m_pRefreshAllAct->setStatusTip(RTDB_REFRESH_ALL);
    m_pRefreshAllAct->setEnabled(false);
    connect(m_pRefreshAllAct, SIGNAL(triggered()), this, SLOT(refreshAllRtdb()));
    //刷新单个点
    m_pRefreshSingleAct->setText(RTDB_REFRESH_SINGLE);
    m_pRefreshSingleAct->setStatusTip(RTDB_REFRESH_SINGLE);
    m_pRefreshSingleAct->setEnabled(false);
    connect(m_pRefreshSingleAct, SIGNAL(triggered()), this, SLOT(refreshSingleRtdb()));
    //保存实时库修改
    m_pSaveRtdbAct->setText(RTDB_SAVE);
    m_pSaveRtdbAct->setStatusTip(RTDB_SAVE);
    m_pSaveRtdbAct->setEnabled(false);
    connect(m_pSaveRtdbAct, SIGNAL(triggered()), this, SLOT(saveRtdbData()));
    //关于
    m_pAboutAct->setText(PCCLIENT_ABOUT);
    m_pAboutAct->setStatusTip(PCCLIENT_ABOUT);
    connect(m_pAboutAct, SIGNAL(triggered()), this, SLOT(onAbout()));
    //关闭
    m_pQuitAct->setText(PCCLIENT_QUIT);
    m_pQuitAct->setStatusTip(PCCLIENT_QUIT);
    connect(m_pQuitAct, SIGNAL(triggered()), this, SLOT(close()));

    //
    m_pAnalyzeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_pModel->setSourceModel(createModel(this));
    m_pTableView->setModel(m_pModel);
    m_pTableView->horizontalHeader()->hide();
    m_pTableView->horizontalHeader()->setStretchLastSection(true);
    m_pTableView->verticalHeader()->setStretchLastSection(true);
    m_pTableView->setRowHeight(TABLE_COMMPKT_PACKET, 200);

    m_pAnalyzeDock->setWidget(m_pTableView);
    //    m_pAnalyzeDock->setWindowIcon(QIcon(":/system/images/analyze.png"));
    m_pAnalyzeDock->setVisible(false);
    this->addDockWidget(Qt::RightDockWidgetArea, m_pAnalyzeDock);

    m_pLogDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    //    m_pLogDock->setWindowIcon(QIcon(":/system/images/256/clipboard.png"));
    m_pLogDock->toggleViewAction()->setIcon(QIcon(":/system/images/256/clipboard.png"));
    m_pLogDock->setMinimumHeight(100);
    m_pLogDock->setWidget(m_pLogTxt);
    m_pLogDock->setVisible(false);
    this->addDockWidget(Qt::BottomDockWidgetArea, m_pLogDock);
    //
    m_pServiceMenu->addAction(m_pCommCfgAct);
    m_pServiceMenu->addAction(m_pRtdbAct);
    m_pServiceMenu->addAction(m_pCommPktAct);
    m_pServiceMenu->addSeparator();
    m_pServiceMenu->addAction(m_pQuitAct);
    //
    m_pFunctionMenu->addAction(m_pTransAct);
    m_pFunctionMenu->addAction(m_pConnTransAct);
    m_pFunctionMenu->addAction(m_pDisconnTransAct);
    m_pFunctionMenu->addAction(m_pCallTransAct);
    m_pFunctionMenu->addAction(m_pPrintTransAct);
    //m_pFunctionMenu->addAction(m_pIec103Act);
    //m_pFunctionMenu->addAction(m_pIec61850Act);
    //
    m_pInterfaceMenu->addAction(m_pLogDock->toggleViewAction());
    m_pHelpMenu->addAction(m_pAboutAct);

    m_pCfgToolBar->addAction(m_pCommCfgAct);
    m_pCfgToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    //
    m_pRtdbToolBar->addAction(m_pRtdbAct);
    m_pRtdbToolBar->addAction(m_pRefreshAllAct);
    m_pRtdbToolBar->addAction(m_pRefreshSingleAct);
    m_pRtdbToolBar->addAction(m_pSaveRtdbAct);
    m_pRtdbToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    //
    m_pPacketToolBar->addAction(m_pCommPktAct);
    m_pPacketToolBar->addAction(m_pStartRollAct);
    m_pPacketToolBar->addAction(m_pStopRollAct);
    m_pPacketToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    //
    m_pFunctionToolBar->addAction(m_pTransAct);
    m_pFunctionToolBar->addAction(m_pConnTransAct);
    m_pFunctionToolBar->addAction(m_pDisconnTransAct);
    m_pFunctionToolBar->addAction(m_pCallTransAct);
    m_pFunctionToolBar->addAction(m_pPrintTransAct);
    //m_pFunctionToolBar->addAction(m_pIec103Act);
    //m_pFunctionToolBar->addAction(m_pIec61850Act);
    m_pFunctionToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    //
    m_pSystemToolBar->addAction(m_pLogDock->toggleViewAction());
    m_pSystemToolBar->addAction(m_pAboutAct);
    m_pSystemToolBar->addAction(m_pQuitAct);
    m_pSystemToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    this->statusBar()->showMessage(PCCLIENT_READY);
}

QAbstractItemModel *PCClient::createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(TABLE_COMMPKT_MAX_NUM + 1, 0, parent);

    model->setHeaderData(TABLE_COMMPKT_MASTER, Qt::Vertical, COMMPKT_MASTER);
    model->setHeaderData(TABLE_COMMPKT_SEND_RECV, Qt::Vertical,
                         COMMPKT_SEND_RECV);
    model->setHeaderData(TABLE_COMMPKT_TIME, Qt::Vertical, COMMPKT_TIME);
    model->setHeaderData(TABLE_COMMPKT_PACKET, Qt::Vertical, COMMPKT_PACKET);
    //
    model->setHeaderData(TABLE_COMMPKT_PACKET_ANALYZE, Qt::Vertical,
                         COMMPKT_PACKET_ANALYZE);

    return model;
}
