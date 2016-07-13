#ifndef EXAMTREE_H
#define EXAMTREE_H

#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QTreeView>
#include <QStandardItem>
#include "pcdefs.h"

class ExaminationTree : public QTreeView {
    Q_OBJECT
public:
    explicit ExaminationTree(QWidget *parent = 0);
    ~ExaminationTree();

    QStandardItemModel *getModel();

    void mousePressEvent(QMouseEvent *event);

signals:
    void treeClicked(const QModelIndex &index);

public slots:
    void onTreeCustomContextMenuRequested(QPoint pos);

private:
    QWidget *m_pParent;
    QStandardItemModel *treeModel;
    QStandardItem *examManage;
    QMenu *treePopMenu;
    QAction *callAction;
};

#endif // EXAMTREE_H
