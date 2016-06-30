#ifndef EXAMINATIONTABLE_H
#define EXAMINATIONTABLE_H

#include <QMenu>
#include <QTableView>
#include <QStandardItemModel>
#include "proxymodel.h"
#include "pcdefs.h"

class ExaminationTable : public QTableView
{
    Q_OBJECT
public:
    explicit ExaminationTable(QWidget *parent = 0);
    ~ExaminationTable();
    //
    QAbstractItemModel *createModel(QObject *parent);
    void fillModel(const QList<QStringList> &exams);

public slots:
    void onTableCustomContextMenuRequested(QPoint pos);

private:
    QWidget *m_pParent;
    ProxyModel *tableModel;
    QMenu *tablePopMenu;
    QAction *printAction;
    QAction *excelAction;
    QAction *csvAction;
};

#endif // EXAMINATIONTABLE_H
