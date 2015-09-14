#ifndef TRANSMITTAB_H
#define TRANSMITTAB_H

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
#include "borderlayout.h"
#include "pcmodel.h"
#include "pcdefs.h"

class TransmitTab : public QWidget
{
    Q_OBJECT
public:
    explicit TransmitTab(QWidget *parent = 0);
    ~TransmitTab(void);
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
    TransmitTree *transmitTree;

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
    QMenu *treePopMenu;
    QMenu *tablePopMenu;
    QAction *callAction;
    QAction *printAction;
    QAction *excelAction;
    QAction *csvAction;

    BorderLayout *layout;

    QTableView *tableView;
    PCModel *m_pAIModel[CHANNEL_MAX];
    PCModel *m_pCOSModel[CHANNEL_MAX];
    PCModel *m_pDOModel[CHANNEL_MAX];
    PCModel *m_pSoeBufferModel[CHANNEL_MAX][IED_MAX];
    int m_nChnlIndex;
    int m_nIedIndex;
    int m_nTypeIndex;
    QPrinter *m_pPrinter;
};

#endif // TRANSMITTAB_H
