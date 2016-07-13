#ifndef LOGDOCK_H
#define LOGDOCK_H
#include <QDockWidget>
//#include <QTextEdit>
#include <QTableView>
#include "proxymodel.h"
#include "pcdefs.h"

class LogDock : public QDockWidget {
public:
    explicit LogDock(const QString &title, QWidget *parent = 0);
    ~LogDock();

//public slots:
    void appendLog(const QString context);

protected:
    QAbstractItemModel * createModel(QObject *parent);

private:
    QTableView *m_pTableView;
    ProxyModel *m_pModel;
//private:
//    QTextEdit *m_pLogTxt;
};

#endif // LOGDOCK_H
