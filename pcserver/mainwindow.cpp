#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDate>
#include "mainwindow.h"
#include "configdialog.h"
#include "xmlparser.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      tcpServer(new TcpServer()),
      db(new DbMySQL()),
      m_pWidget(new TabWidget(this)),
      m_pAnalyzeDock(new AnalyzeDock(COMMPKT_PACKET_ANALYZE, this)),
      m_pLogDock(new LogDock(COMMPKT_SYSTEM_LOG, this)),
      m_pServiceMenu(this->menuBar()->addMenu(MENU_SERVICE)),
      m_pFunctionMenu(this->menuBar()->addMenu(MENU_FUNCTION)),
      m_pInterfaceMenu(this->menuBar()->addMenu(MENU_INTERFACE)),
      m_pHelpMenu(this->menuBar()->addMenu(MENU_HELP)),
      m_pCfgToolBar(this->addToolBar(tr("Config"))),
      m_pSystemToolBar(this->addToolBar(tr("System"))),
      m_pConfigAct(new QAction(QIcon(":/res/images/256/connect.png"), tr("&Communication Config"), this)),
      m_pQuitAct(new QAction(QIcon(":/res/images/256/close.png"), tr("&Quit System"), this)),
      m_pAboutAct(new QAction(QIcon(":/res/images/256/info.png"), tr("&About PCServer"), this))
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("PCServer"));

    this->setWindowIcon(QIcon(":/res/images/PCServer.png"));
    this->setWindowTitle(PCSERVER_CONTEXT);
    this->setAutoFillBackground(true);
    this->setUnifiedTitleAndToolBarOnMac(false);
    this->setCentralWidget(m_pWidget);
    this->drawWindows();
    this->resize(QApplication::desktop()->width(), QApplication::desktop()->height());
    //
    connect(tcpServer,&TcpServer::connectClient,m_pWidget,&TabWidget::onSocketConnect);
    connect(tcpServer,&TcpServer::sockDisConnect,m_pWidget,&TabWidget::onSocketDisConnect);
}

MainWindow::~MainWindow()
{
    if(nullptr != tcpServer)
    {
        if(tcpServer->isListening())
            tcpServer->close();
        delete tcpServer, tcpServer = nullptr;
    }

    if(nullptr != m_pWidget)
        delete m_pWidget, m_pWidget = nullptr;
}

void MainWindow::drawWindows()
{
    m_pConfigAct->setText(COMMUNICATION_CONFIG);
    m_pConfigAct->setStatusTip(COMMUNICATION_CONFIG);
    connect(m_pConfigAct, SIGNAL(triggered()), this, SLOT(onConfigDlg()));

    //关于
    m_pAboutAct->setText(PCSERVER_ABOUT);
    m_pAboutAct->setStatusTip(PCSERVER_ABOUT);
    connect(m_pAboutAct, SIGNAL(triggered()), this, SLOT(onAbout()));
    //关闭
    m_pQuitAct->setText(PCSERVER_QUIT);
    m_pQuitAct->setStatusTip(PCSERVER_QUIT);
    connect(m_pQuitAct, SIGNAL(triggered()), this, SLOT(close()));

    //
    m_pAnalyzeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_pAnalyzeDock->setVisible(false);
    this->addDockWidget(Qt::RightDockWidgetArea, m_pAnalyzeDock);

    m_pLogDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    m_pLogDock->toggleViewAction()->setIcon(QIcon(":/res/images/256/clipboard.png"));
    m_pLogDock->toggleViewAction()->setStatusTip(COMMPKT_SYSTEM_LOG);
    m_pLogDock->setMinimumHeight(100);
    m_pLogDock->setVisible(false);
    this->addDockWidget(Qt::BottomDockWidgetArea, m_pLogDock);
    //
    m_pServiceMenu->addAction(m_pConfigAct);
    m_pServiceMenu->addAction(m_pQuitAct);
    //
    m_pInterfaceMenu->addAction(m_pLogDock->toggleViewAction());
    m_pHelpMenu->addAction(m_pAboutAct);

    m_pCfgToolBar->addAction(m_pConfigAct);
    m_pCfgToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //
    m_pSystemToolBar->addAction(m_pLogDock->toggleViewAction());
    m_pSystemToolBar->addAction(m_pAboutAct);
    m_pSystemToolBar->addAction(m_pQuitAct);
    m_pSystemToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    this->statusBar()->showMessage(PCSERVER_READY);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    switch (QMessageBox::information(this, QUIT_TITLE, QUIT_TEXT, CONFIRM, CANCEL, 0, 1))
    {
    case 0:
    {
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

void MainWindow::appendLog(const QString context)
{
    m_pLogDock->appendLog(context);
}

void MainWindow::onConfigDlg()
{
    ConfigDialog* ccd = new ConfigDialog(this);
    if (ccd->exec() == QDialog::Accepted)
    {
        SERVER_INFO server;
        server.ipAddress = "127.0.0.1";
        server.listenPort = ccd->getGeneralTab()->getListenPort();
        ccd->saveConfig(&server);

        if(tcpServer->isListening())
            tcpServer->close();
        tcpServer->listen(QHostAddress::Any, server.listenPort.toUInt());
    }

    ccd->close();
    delete ccd;
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, PCSERVER_ABOUT, ABOUT_CONTEXT);
}
