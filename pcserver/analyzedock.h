#ifndef ANALYZEDOCK_H
#define ANALYZEDOCK_H

#include <QDockWidget>
#include <QTableView>
#include "proxymodel.h"
#include "pcdefs.h"

class AnalyzeDock : public QDockWidget {
public:
    explicit AnalyzeDock(const QString &title, QWidget *parent = 0);
    ~AnalyzeDock();

protected:
    QAbstractItemModel * createModel(QObject *parent);

private:
    QTableView *m_pTableView;
    ProxyModel *m_pModel;
};

#endif // ANALYZEDOCK_H
