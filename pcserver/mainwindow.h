#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QProgressDialog>

#include "tcpserver.h"
#include "tabwidget.h"
#include "proxymodel.h"
#include "analyzedock.h"
#include "logdock.h"
#include "pcdefs.h"
#include "utils.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void drawWindows();
    void closeEvent(QCloseEvent *event) override;
    void appendLog(const QString context);

private slots:
    void onAbout();
    void onFullScreen(void);
    void onConfigDlg();
    void onExamManageTab();
    void onConnManageTab();

private:
    //TCP Server
    TcpServer *tcpServer = nullptr;
    //Centre Widget
    TabWidget *m_pWidget = nullptr;
    AnalyzeDock *m_pAnalyzeDock = nullptr;
    LogDock *m_pLogDock = nullptr;

    QMenu *m_pServiceMenu;
    QMenu *m_pFunctionMenu;
    QMenu *m_pInterfaceMenu;
    QMenu *m_pHelpMenu;

    QToolBar *m_pCfgToolBar;
    QToolBar *m_pFunctionToolBar;
    QToolBar *m_pSystemToolBar;
    QToolBar *m_pViewToolBar;

    //Action
    QAction *m_pConfigAct;
    QAction *m_pExamManageAct;
    QAction *m_pCommManageAct;
    QAction *m_pFullScreenAct;
    QAction *m_pQuitAct;
    QAction *m_pAboutAct;

    bool m_bFullScreen;
};

#endif // MAINWINDOW_H
