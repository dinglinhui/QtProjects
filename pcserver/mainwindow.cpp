#include <QApplication>
#include <QDesktopWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDate>
#include <QtOpenGL>

#include "mainwindow.h"
#include "configdialog.h"
#include "xmlparser.h"
#include "ComboboxItem.h"
#include "NoFocusFrameDelegate.h"

extern SessionInfo sessionInfo;
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        tcpServer(new TcpServer()),
        m_pWidget(new TabWidget(this)),
        m_pAnalyzeDock(new AnalyzeDock(COMMPKT_PACKET_ANALYZE, this)),
        m_pLogDock(new LogDock(COMMPKT_SYSTEM_LOG, this)),
        m_pServiceMenu(this->menuBar()->addMenu(MENU_SERVICE)),
        m_pFunctionMenu(this->menuBar()->addMenu(MENU_FUNCTION)),
        m_pInterfaceMenu(this->menuBar()->addMenu(MENU_INTERFACE)),
        m_pHelpMenu(this->menuBar()->addMenu(MENU_HELP)),
        m_pCfgToolBar(this->addToolBar(tr("Config"))),
        m_pFunctionToolBar(this->addToolBar(tr("Function"))),
        m_pSystemToolBar(this->addToolBar(tr("System"))),
        m_pViewToolBar(this->addToolBar(tr("View"))),
        m_pConfigAct(new QAction(QIcon(":/res/images/256/connect.png"), tr("&Communication Config"), this)),
        m_pExamManageAct(new QAction(QIcon(":/res/images/256/book.png"), tr("&Exam Manage"), this)),
        m_pCommManageAct(new QAction(QIcon(":/res/images/256/virus.png"), tr("&Communication Manage"), this)),
        m_pFullScreenAct(new QAction(QIcon(":/res/images/fullscreenIcon.png"), tr("&Full Screen"), this)),
        m_pQuitAct(new QAction(QIcon(":/res/images/256/close.png"), tr("&Quit System"), this)),
        m_pAboutAct(new QAction(QIcon(":/res/images/256/info.png"), tr("&About PCServer"), this)),
        m_bFullScreen(true) {
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("PCServer"));

    this->setWindowIcon(QIcon(":/res/images/PCServer.png"));
    this->setWindowTitle(PCSERVER_CONTEXT);
    this->setAutoFillBackground(true);
    this->setUnifiedTitleAndToolBarOnMac(false);
    this->setCentralWidget(m_pWidget);
    this->drawWindows();
    this->resize(QApplication::desktop()->width()*2/3, QApplication::desktop()->height()*2/3);
    //
    connect(tcpServer, &TcpServer::connectClient, m_pWidget, &TabWidget::onSocketConnect);
    connect(tcpServer, &TcpServer::sockDisConnect, m_pWidget, &TabWidget::onSocketDisConnect);

    //m_pWidget->addWelcomeTab();
    //    db->getSystemInfo(sessionInfo.sessionId.adminId);
}

MainWindow::~MainWindow() {
    if (nullptr != tcpServer) {
        if (tcpServer->isListening())
            tcpServer->close();
        delete tcpServer, tcpServer = nullptr;
    }

    if (nullptr != m_pWidget)
        delete m_pWidget, m_pWidget = nullptr;
}

void MainWindow::drawWindows() {
    m_pConfigAct->setText(COMMUNICATION_CONFIG);
    connect(m_pConfigAct, SIGNAL(triggered()), this, SLOT(onConfigDlg()));

    m_pExamManageAct->setText(EXAMINATION_MANAGE);
    connect(m_pExamManageAct, SIGNAL(triggered()), this, SLOT(onExamManageTab()));

    m_pCommManageAct->setText(COMMUNICATION_MANAGE);
    connect(m_pCommManageAct, SIGNAL(triggered()), this, SLOT(onConnManageTab()));

    m_pFullScreenAct->setText(FULL_SCREEN);
    connect(m_pFullScreenAct, SIGNAL(triggered()), this, SLOT(onFullScreen()));

    m_pAboutAct->setText(PCSERVER_ABOUT);
    connect(m_pAboutAct, SIGNAL(triggered()), this, SLOT(onAbout()));

    m_pQuitAct->setText(PCSERVER_QUIT);
    connect(m_pQuitAct, SIGNAL(triggered()), this, SLOT(close()));

    //
    m_pAnalyzeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_pAnalyzeDock->setVisible(false);
    this->addDockWidget(Qt::RightDockWidgetArea, m_pAnalyzeDock);

    m_pLogDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    m_pLogDock->toggleViewAction()->setIcon(QIcon(":/res/images/256/clipboard.png"));
    m_pLogDock->setMinimumHeight(100);
    m_pLogDock->setVisible(false);
    this->addDockWidget(Qt::BottomDockWidgetArea, m_pLogDock);
    //
    m_pServiceMenu->addAction(m_pConfigAct);
    m_pServiceMenu->addAction(m_pQuitAct);
    m_pFunctionMenu->addAction(m_pCommManageAct);
    m_pFunctionMenu->addAction(m_pExamManageAct);
    //
    m_pInterfaceMenu->addAction(m_pFullScreenAct);
    m_pInterfaceMenu->addAction(m_pLogDock->toggleViewAction());
    m_pHelpMenu->addAction(m_pAboutAct);

    this->menuBar()->setDefaultUp(false);

    m_pCfgToolBar->addAction(m_pConfigAct);
    m_pCfgToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    m_pFunctionToolBar->addAction(m_pCommManageAct);
    m_pFunctionToolBar->addAction(m_pExamManageAct);
    m_pFunctionToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    m_pSystemToolBar->addAction(m_pLogDock->toggleViewAction());
    m_pSystemToolBar->addAction(m_pAboutAct);
    m_pSystemToolBar->addAction(m_pQuitAct);
    m_pSystemToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pViewToolBar->addWidget(spacer);

    m_pViewToolBar->addAction(m_pFullScreenAct);
    m_pViewToolBar->addSeparator();

    QLabel* label = new QLabel("Layout:");
    m_pViewToolBar->addWidget(label);

    QComboBox *comboBox = new QComboBox(m_pViewToolBar);
    comboBox->setMinimumWidth(150);
    comboBox->addItem("defaule");
    comboBox->addItem("classic");
    comboBox->addItem("expert");
    comboBox->insertSeparator(3);
    comboBox->addItem("Save");
    comboBox->addItem("Load");

//    QListWidget* m_listWidget = new QListWidget(this);
//    m_listWidget->setItemDelegate(new NoFocusFrameDelegate(this));
//    comboBox->setEditable(false);
//    comboBox->setModel(m_listWidget->model());
//    comboBox->setView(m_listWidget);
//    comboBox->setCurrentIndex(0);

//    for (int i = 0; i < 5; ++i)
//    {
//        ComboboxItem* item = new ComboboxItem(comboBox);
//        item->setLabelContent(QString("Account") + QString::number(i, 10));
//        //connect(item, SIGNAL(chooseAccount(const QString&)), this, SLOT(onChooseAccount(const QString&)));
//        QListWidgetItem* widgetItem = new QListWidgetItem(m_listWidget);
//        m_listWidget->setItemWidget(widgetItem, item);
//    }


    QWidgetAction *checkableAction = new QWidgetAction(m_pViewToolBar);
    checkableAction->setDefaultWidget(comboBox);
    m_pViewToolBar->addAction(checkableAction);
    m_pViewToolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    //

    QString dateTime = QDateTime::currentDateTimeUtc().toString();
    QString lastLoginTime = sessionInfo.sessionId.adminLoginDate;
    if (lastLoginTime == "")
        lastLoginTime = dateTime;

    sessionInfo.sessionId.adminLoginDate = dateTime;
//    db->updateAdminInfo();

    this->statusBar()->showMessage(
            QString(PCSERVER_ADMIN).append(sessionInfo.sessionId.adminName).append("(").append(table_authority[sessionInfo.sessionId.adminLevel]).append(")  ").append(ADMIN_LOGIN_DATE).append(
                    dateTime).append("  ").append(ADMIN_LAST_LOGIN_DATE).append(lastLoginTime));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    switch (QMessageBox::information(this, QUIT_TITLE, QUIT_TEXT, CONFIRM, CANCEL, 0, 1)) {
    case 0: {
        event->accept();
        break;
    }
    case 1:
    default: {
        event->ignore();
        break;
    }
    }
}

void MainWindow::appendLog(const QString context) {
    m_pLogDock->appendLog(context);
}

void MainWindow::onFullScreen(void) {
    if (m_bFullScreen) {
        //menuBar()->hide();
        showFullScreen();
    } else {
        //menuBar()->show();
        showNormal();
    }
    m_bFullScreen = !m_bFullScreen;
}

void MainWindow::onAbout() {
    QMessageBox::about(this, PCSERVER_ABOUT, ABOUT_CONTEXT);
}

void MainWindow::onConfigDlg() {
    ConfigDialog* ccd = new ConfigDialog(this);
    if (ccd->exec() == QDialog::Accepted) {
        ServerInfo serverInfo;
        serverInfo.ipAddress = "127.0.0.1";
        serverInfo.listenPort = ccd->getGeneralTab()->getListenPort();
        ccd->saveConfig(&serverInfo);

        if (tcpServer->isListening())
            tcpServer->close();
        tcpServer->listen(QHostAddress::Any, serverInfo.listenPort.toUInt());
        sessionInfo.systemInfo.serverInfo = serverInfo;
//        db->updateSystemInfo(sessionInfo.sessionId.adminId);
    }

    ccd->close();
    delete ccd;
}

void MainWindow::onExamManageTab() {
    m_pWidget->addExamManageTab();
    this->update();
}

void MainWindow::onConnManageTab() {
    m_pWidget->addConnManageTab();
    this->update();
}
