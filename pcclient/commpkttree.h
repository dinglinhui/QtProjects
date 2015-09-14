#ifndef COMMPKTTREE_H
#define COMMPKTTREE_H

#include <QTreeView>
#include <QList>
#include <QStandardItem>
#include <QMouseEvent>

class CommPktTree: public QTreeView
{
	Q_OBJECT

public:
	explicit CommPktTree(QWidget *parent = 0);
	//
	QString getCurrentItemName();
	QString getCurrentItemName(QString &name);
	//
	void insertItems(const QString &text);
	void insertItems(QStandardItem *root, const QString &text);
	//
	bool searchItems(const QString &text);
	//
	QList<QStandardItem *> returnTheItems();
	QList<QStandardItem *> returnTheItems(const QString &text);

	void mousePressEvent(QMouseEvent *event);

	QStandardItemModel *getModel();

signals:
	void treeClicked(const QModelIndex &index);

private:
	QStandardItemModel *model;
	QStandardItem *root;
	int m_nIndex;
};

#endif // TREEVIEW_H
