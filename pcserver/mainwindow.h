#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QMenu>
#include <QAction>
#include <QProgressDialog>

#include "tcpserver.h"
#include "tabwidget.h"
#include "proxymodel.h"
#include "analyzedock.h"
#include "logdock.h"
#include "dbmysql.h"
#include "pcdefs.h"
#include "utils.h"

class MainWindow : public QMainWindow
{
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
    void onConfigDlg();
    void onExamManageTab();
    void onConnManageTab();

private:
    //TCP Server
    TcpServer *tcpServer = nullptr;
    //MySQL
    DbMySQL *db = nullptr;
    //Centre Widget
    TabWidget *m_pWidget = nullptr;
    //分析Dock
    AnalyzeDock *m_pAnalyzeDock = nullptr;
    //日志Dock
    LogDock *m_pLogDock;

    //菜单
    QMenu *m_pServiceMenu;
    QMenu *m_pFunctionMenu;
    QMenu *m_pInterfaceMenu;
    QMenu *m_pHelpMenu;
    //工具栏
    QToolBar *m_pCfgToolBar;//配置工具栏
    QToolBar *m_pFunctionToolBar;//功能工具栏
    QToolBar *m_pSystemToolBar;//系统工具栏

    //Action
    QAction *m_pConfigAct;
    QAction *m_pExamManageAct;
    QAction *m_pCommManageAct;
    QAction *m_pQuitAct;
    QAction *m_pAboutAct;
};

#endif // MAINWINDOW_H
