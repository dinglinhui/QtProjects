#ifndef RTDBTREE_H
#define RTDBTREE_H

#include <QTreeView>
#include <QList>
#include <QStandardItem>
#include <QMouseEvent>

class RtdbTree: public QTreeView
{
	Q_OBJECT
public:
	explicit RtdbTree(QWidget *parent = 0);

	void mousePressEvent(QMouseEvent *event);

	QStandardItemModel *getModel();

signals:
	void treeClicked(const QModelIndex &index);

private:
	QStandardItemModel *model;
};

#endif // TREEVIEW_H
