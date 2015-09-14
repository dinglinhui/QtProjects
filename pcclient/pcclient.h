#ifndef PCCLIENT_H_
#define PCCLIENT_H_

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QMenu>
#include <QAction>
#include <QProgressDialog>
#include "pcdefs.h"
#include "uddthread.h"
#include "transmitthread.h"
#include "pcwidget.h"

class PCClient: public QMainWindow
{
    Q_OBJECT

public:
    PCClient();
    ~PCClient();

protected:
    void closeEvent(QCloseEvent *event);

private slots:

    void onCommCfgDlg();
    void onRtdbDataTab();
    void onCommPktTab();
    void onTransmitTab();
    void onIEC103Tab();
    void onIEC61850Tab();
    void onAbout();
    //
    void enableRefreshSingleAction();
    void enableSaveDataAction();
    //
    void startRolling();
    void stopRolling();
    //
    void refreshAllRtdb();
    void refreshSingleRtdb();
    void saveRtdbData();
    void saveRtdbData(QMap<int, QStringList> &map);
    //
    void analyzePacket(const QStringList &list);
    //
    void onConnTransmit();
    void onDisconnTransmit();
    void onCallTransmit();
    void onPrintTransmit();
    void onEndRequest();
    //
    void onSaveProcesser(const QString & info);
    //
    void onRtdbTreeClicked(const QModelIndex & index);
    void onCommPktTreeClicked(const QModelIndex & index);
    void onTransmitTreeClicked(const QModelIndex & index);
    //
    void switchStation(const QByteArray &buffer);
    //
    void connectRequest();
    void disconnectRequest();

public:
    void switchRequest(QByteArray &buffer, int nRequestType, int nDataNum = 0, int nRecordConut = 0);
    void makeRequestReport(QByteArray &buffer, int nRequestType);
    void makeRequestTransmit(QByteArray &buffer, int nRequestType, int nChannel);
    void makeRecordAskBuffer(QByteArray &buffer, int nReportType, int nRecordCount);
    void makeRtdbSendReport(QByteArray &buffer, int nReportType, int nDataNum, int nRecordConut);
    void appendToLog(const QString &str);

private:
    void drawWindows();

    void initUddThread(SERVER_INFO *pServer);
    void initTransmitThread(SERVER_INFO *pServer);
    void startUddThread();
    void startTransmitThread();
    //
    QAbstractItemModel *createModel(QObject *parent);

    //套接字线程
    UddThread *m_pUddThread;
    //转发表线程
    TransmitThread *m_pTransThread;
    //系统Widget
    PCWidget *m_pWidget;
    //报文分析Dock
    QDockWidget *m_pAnalyzeDock;
    QTableView *m_pTableView;
    PCModel *m_pModel;
    //日志Dock
    QDockWidget *m_pLogDock;
    QTextEdit *m_pLogTxt;
    //菜单
    QMenu *m_pServiceMenu;
    QMenu *m_pFunctionMenu;
    QMenu *m_pInterfaceMenu;
    QMenu *m_pHelpMenu;
    //工具栏
    QToolBar *m_pCfgToolBar;//配置工具栏
    QToolBar *m_pRtdbToolBar;//实时库工具栏
    QToolBar *m_pPacketToolBar;//报文工具栏
    QToolBar *m_pFunctionToolBar;//转发表工具栏
    QToolBar *m_pSystemToolBar;//系统工具栏

    //Action
    QAction *m_pCommCfgAct;
    QAction *m_pCommPktAct;
    QAction *m_pStartRollAct;
    QAction *m_pStopRollAct;
    //
    QAction *m_pTransAct;
    QAction *m_pConnTransAct;
    QAction *m_pDisconnTransAct;
    QAction *m_pCallTransAct;
    QAction *m_pPrintTransAct;
    //QAction *m_pIec103Act;
    //QAction *m_pIec61850Act;
    QAction *m_pRtdbAct;
    QAction *m_pRefreshAllAct;
    QAction *m_pRefreshSingleAct;
    QAction *m_pSaveRtdbAct;
    QAction *m_pQuitAct;
    QAction *m_pAboutAct;

    bool masterFlag;
    bool m_bRequestEnd;
};

#endif /* PCCLIENT_H_ */
