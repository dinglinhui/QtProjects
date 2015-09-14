#ifndef COMMPKTTAB_H_
#define COMMPKTTAB_H_

#include <QWidget>
#include <QTreeView>
#include <QTextEdit>
#include <QTableView>
#include <QTabWidget>
#include <QItemSelection>
#include <QStringList>
#include <QStandardItemModel>
#include "commpkttree.h"
#include "borderlayout.h"
#include "pcmodel.h"

class CommPktTab : public QWidget
{
    Q_OBJECT

public:
    explicit CommPktTab(QWidget *parent = 0);
    //
    void displayReport(const QByteArray &buffer);
    void addPacketInfo(QAbstractItemModel *model, const QStringList &list);
    //
    QAbstractItemModel *createModel(QObject *parent);
    //
    bool getRolling();
    void setRolling(bool nRolling);
    void analyzeCommPkt(int rowIndex);
    void masterFilterChanged(const QString & master);
    bool removeDirWithContent(const QString &dirName);

    CommPktTree *commpktTree;

private slots:
    void on_customContextMenuRequested(QPoint pos);
    void on_doubleClicked(const QModelIndex &index);
    void on_clearActionTriggered();
    void on_saveActionTriggered();
    void on_analyzeActionTriggered();

signals:
//    void savePacketSignal(const QString &);
    void analyzePacketSignal(const QStringList &);
    //void analyzeMasterSignal(const QString &);

private:
    QMenu *popMenu;
    QAction *analyzeAction;
    QAction *clearAction;
    QAction *saveAction;
    BorderLayout *layout;

    QTableView *tableView;
    PCModel *proxyModel;

    bool m_bRolling;
    int m_nSaveTimes;
};

#endif /* COMMPKTTAB_H_ */
