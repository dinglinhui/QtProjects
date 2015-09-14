#include <QModelIndex>
#include <QDebug>
#include "rtdbtree.h"
#include "pcdefs.h"

RtdbTree::RtdbTree(QWidget *parent) :
		QTreeView(parent)
{
	model = new QStandardItemModel(RTDB_MAX_NUM, 1);
	model->setHeaderData(0, Qt::Horizontal, RTDB_DATA);

	QStandardItem *item1 = new QStandardItem(XML_ELEMENT_MX);
	item1->setIcon(QIcon(":/system/images/Red Ball.png"));
	QStandardItem *item2 = new QStandardItem(XML_ELEMENT_ST);
	item2->setIcon(QIcon(":/system/images/Yellow Ball.png"));
	QStandardItem *item3 = new QStandardItem(XML_ELEMENT_CO);
	item3->setIcon(QIcon(":/system/images/Orange Ball.png"));
	QStandardItem *item4 = new QStandardItem(XML_ELEMENT_SP);
	item4->setIcon(QIcon(":/system/images/Blue Ball.png"));
	QStandardItem *item5 = new QStandardItem(XML_ELEMENT_SG);
	item5->setIcon(QIcon(":/system/images/Green Ball.png"));
	QStandardItem *item6 = new QStandardItem(XML_ELEMENT_SE);
	item6->setIcon(QIcon(":/system/images/Purple Ball.png"));

	model->setItem(RTDB_MX, 0, item1);
	model->setItem(RTDB_ST, 0, item2);
	model->setItem(RTDB_CO, 0, item3);
	model->setItem(RTDB_SP, 0, item4);
	model->setItem(RTDB_SG, 0, item5);
	model->setItem(RTDB_SE, 0, item6);

	this->setModel(model);
}

QStandardItemModel *RtdbTree::getModel()
{
	return model;
}

void RtdbTree::mousePressEvent(QMouseEvent *event)
{
	QTreeView::mousePressEvent(event);

	QModelIndex index = currentIndex();
	if (event->buttons() == Qt::LeftButton)
	{
		emit treeClicked(index);
	}
}
