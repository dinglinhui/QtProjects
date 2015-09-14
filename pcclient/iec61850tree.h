#ifndef IEC61850TREE_H_
#define IEC61850TREE_H_

#include <QTreeView>
#include <QList>
#include <QStandardItem>
#include <QMouseEvent>

class IEC61850Tree: public QTreeView
{
	Q_OBJECT
public:
	explicit IEC61850Tree(QWidget *parent = 0);
	virtual ~IEC61850Tree();
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
#endif /* IEC61850TREE_H_ */
