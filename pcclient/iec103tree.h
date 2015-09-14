/*
 * IEC103Tree.h
 *
 *  Created on: 2014/2/26
 *      Author: dinglinhui
 */

#ifndef IEC103TREE_H_
#define IEC103TREE_H_

#include <QTreeView>
#include <QList>
#include <QStandardItem>
#include <QMouseEvent>

class IEC103Tree: public QTreeView
{
	Q_OBJECT
public:
	explicit IEC103Tree(QWidget *parent = 0);
	virtual ~IEC103Tree();
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
};

#endif /* IEC103Tree_H_ */
