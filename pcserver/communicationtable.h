#ifndef COMMUNICATIONTABLE_H
#define COMMUNICATIONTABLE_H

#include <QTableView>
#include <QStandardItemModel>
#include <QMenu>
#include <QAction>
#include "proxymodel.h"
#include "pcdefs.h"

class CommunicationTable : public QTableView
{
    Q_OBJECT
public:
    explicit CommunicationTable(QWidget *parent = 0);
    ~CommunicationTable();
    //
    QAbstractItemModel *createModel(QObject *parent);

public slots:
    void onTableCustomContextMenuRequested(QPoint pos);

private:
    ProxyModel *tableModel;
    QMenu *tablePopMenu;
    QAction *printAction;
    QAction *excelAction;
    QAction *csvAction;
};

#endif // COMMUNICATIONTABLE_H
