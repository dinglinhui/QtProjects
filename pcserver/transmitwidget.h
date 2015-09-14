#ifndef TransmitWidget_H
#define TransmitWidget_H

#include <QWidget>
#include <QTreeView>
#include <QTextEdit>
#include <QTableView>
#include <QTabWidget>
#include <QItemSelection>
#include <QStringList>
#include <QStandardItemModel>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include "transmittree.h"
#include "transmittable.h"
#include "transmitwidget.h"
#include "borderlayout.h"
#include "proxymodel.h"
#include "pcdefs.h"

class TransmitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TransmitWidget(QWidget *parent = 0);
    ~TransmitWidget(void);
    //
    TransmitTree * getTransmitTree();
    TransmitTable * getTransmitTable();
    //
    QAbstractItemModel *createAIModel(QObject *parent);
    QAbstractItemModel *createCOSModel(QObject *parent);
    QAbstractItemModel *createDOModel(QObject *parent);
    QAbstractItemModel *createSoeBufferModel(QObject *parent);
    void clearModel(int chnlIndex, int iedIndex, int typeIndex);
    void changeModel(int chnlIndex, int iedIndex, int typeIndex);
    //
    bool setupPrinter();
    bool setupPage();
    //
    void displayTransmitTable(const QByteArray &buffer, int dbIndex);
    //
signals:
    void endSignl();
    void callSignl();
    void saveSignl(const QString & info);

public slots:
    void printTransmit();
    void onPrint(QPrinter *pPrinter);
    void onCallTriggered();
    void onExportExcelTriggered();
    void onExportCsvTriggered();
    void onTreeCustomContextMenuRequested(QPoint pos);
    void onTableCustomContextMenuRequested(QPoint pos);

private:
    TransmitTree *transmitTree;
    TransmitTable *transmitTable;
    //
    QMenu *treePopMenu;
    QMenu *tablePopMenu;
    //
    QAction *callAction;
    QAction *printAction;
    QAction *excelAction;
    QAction *csvAction;
    //
    ProxyModel *m_pAIModel[CHANNEL_MAX];
    ProxyModel *m_pCOSModel[CHANNEL_MAX];
    ProxyModel *m_pDOModel[CHANNEL_MAX];
    ProxyModel *m_pSoeBufferModel[CHANNEL_MAX][IED_MAX];
    //
    QPrinter *m_pPrinter;
    //
    int m_nChnlIndex;
    int m_nIedIndex;
    int m_nTypeIndex;
};

#endif // TransmitWidget_H
