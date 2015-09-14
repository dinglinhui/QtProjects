#include <QModelIndex>
#include <QDebug>
#include "commpkttree.h"
#include "pcdefs.h"

CommPktTree::CommPktTree(QWidget *parent) :
		QTreeView(parent)
{
	m_nIndex = 0;
	//
	model = new QStandardItemModel(1, 1);
	model->setHeaderData(0, Qt::Horizontal, COMMUNICATION_PACKET);
	//
	root = new QStandardItem(COMMUNICATION_PACKET);
	root->setIcon(QIcon(":/system/images/256/binoculars.png"));
	model->setItem(0, 0, root);

	this->setModel(model);
}

QString CommPktTree::getCurrentItemName()
{
	QString name;
	return getCurrentItemName(name);
}

QString CommPktTree::getCurrentItemName(QString &name)
{
	QModelIndex index = this->currentIndex();
	if (index.parent().row() == -1)
	{
		name = COMMUNICATION_PACKET;
		return QString("");
	}
	else
	{
		name = COMMUNICATION_PACKET + tr("_") + model->data(index).toString();
		return model->data(index).toString();
	}
}

void CommPktTree::insertItems(const QString &text)
{
	insertItems(root, text);
}

void CommPktTree::insertItems(QStandardItem *item, const QString &text)
{
	QStandardItem *item1 = new QStandardItem(text);
	if (m_nIndex == 1)
	{
		item1->setIcon(QIcon(":/system/images/tag_green.png"));
		m_nIndex = 0;
	}
	else
	{
		item1->setIcon(QIcon(":/system/images/tag_blue.png"));
		m_nIndex = 1;
	}
	item->appendRow(item1);
}

bool CommPktTree::searchItems(const QString &text)
{
	QList<QStandardItem *> list = this->returnTheItems(text);
	if (list.isEmpty())
	{
		return false;
	}

	return true;
}

QList<QStandardItem *> CommPktTree::returnTheItems()
{
	return model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> CommPktTree::returnTheItems(const QString &text)
{
	return model->findItems(text, Qt::MatchWildcard | Qt::MatchRecursive);
}

QStandardItemModel *CommPktTree::getModel()
{
	return model;
}

void CommPktTree::mousePressEvent(QMouseEvent *event)
{
	QTreeView::mousePressEvent(event);

	if (event->buttons() == Qt::LeftButton)
	{
		emit treeClicked(currentIndex());
	}
}
