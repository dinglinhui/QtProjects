#ifndef RTDBTAB_H_
#define RTDBTAB_H_

#include <QWidget>
#include <QTreeView>
#include <QTextEdit>
#include <QTableView>
#include <QTabWidget>
#include <QItemSelection>
#include <QStringList>
#include <QStandardItemModel>
#include "rtdbtree.h"
#include "borderlayout.h"
#include "pcmodel.h"

class RtdbTab : public QWidget
{
    Q_OBJECT

public:
    explicit RtdbTab(QWidget *parent = 0);

    void displayRtdbTable(const QByteArray &buffer, int dbIndex);
    void updateRtdbTable(const QByteArray &buffer, int dbIndex);
    void addRtdbData(QAbstractItemModel *model, const QStringList &list);
    void addRtdbData(QAbstractItemModel *model, int index, const QStringList &list);
    int  delRtdbData(QAbstractItemModel *model, int dbIndex, const int saddr);
    QAbstractItemModel *createModel(QObject *parent);
    void changeModel(int index = 0);
    void clearModel(int index = 0);
    bool isModelEmpty();
    int getCurrentRow(QStringList &list);
    //
    void setEditFlag();
    void clearEditFlag();
    QMap<int, QStringList>& getEditMap();
    void clearEditMap();

    RtdbTree *rtdbTree;

private slots:
    void on_customContextMenuRequested(QPoint pos);
    void on_clicked(const QModelIndex & index);
    void on_doubleClicked(const QModelIndex & index);
    void on_refreshAllActionTriggered();
    void on_refreshSingleActionTriggered();
    void on_saveRtdbActionTriggered();
    void on_testRtdbActionTriggered();

signals:
    void enableRefreshSingleSignal();
    void enableSaveDataSignal();
    void refreshAllRtdbSignal();
    void refreshSingleRtdbSignal();
    void saveRtdbDataSignal(QMap<int, QStringList> &map);

private:
    QMenu *popMenu;
    QAction *refreshAllAction;
    QAction *refreshSingleAction;
    QAction *saveRtdbAction;
    BorderLayout *layout;

    QTableView *tableView;
    PCModel *proxyModel;
    QMap<int, QStringList> m_editMap;

    int m_dbIndex;
    int m_lastEditIndex;
};

#endif /* RTDBTAB_H_ */
