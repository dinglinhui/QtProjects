/*
 * IEC61850Tree.cpp
 *
 *  Created on: 2014年2月26日
 *      Author: dinglinhui
 */

#include <QModelIndex>
#include <QDebug>
#include "iec61850tree.h"
#include "pcdefs.h"

IEC61850Tree::IEC61850Tree(QWidget *parent) :
        QTreeView(parent)
{
    model = new QStandardItemModel(1, 1);
    model->setHeaderData(0, Qt::Horizontal, COMMUNICATION_MASTER);
    //
    root = new QStandardItem(COMMUNICATION_MASTER);
    root->setIcon(QIcon(":/system/images/256/world.png"));
    model->setItem(0, 0, root);

    this->setModel(model);
}

IEC61850Tree::~IEC61850Tree()
{

}

QString IEC61850Tree::getCurrentItemName()
{
    QString name;
    return getCurrentItemName(name);
}

QString IEC61850Tree::getCurrentItemName(QString &name)
{
    QModelIndex index = this->currentIndex();
    if (index.parent().row() == -1)
    {
        name = COMMUNICATION_MASTER;
        return QString("");
    }
    else
    {
        name = COMMUNICATION_MASTER + tr("_") + model->data(index).toString();
        return model->data(index).toString();
    }
}

void IEC61850Tree::insertItems(const QString &text)
{
    insertItems(root, text);
}

void IEC61850Tree::insertItems(QStandardItem *item, const QString &text)
{
    QStandardItem *item1 = new QStandardItem(text);
    item1->setIcon(QIcon(":/system/images/tag_blue.png"));
    item->appendRow(item1);
}

bool IEC61850Tree::searchItems(const QString &text)
{
    QList<QStandardItem *> list = this->returnTheItems(text);
    if (list.isEmpty())
    {
        return false;
    }

    return true;
}

QList<QStandardItem *> IEC61850Tree::returnTheItems()
{
    return model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> IEC61850Tree::returnTheItems(const QString &text)
{
    return model->findItems(text, Qt::MatchWildcard | Qt::MatchRecursive);
}

QStandardItemModel *IEC61850Tree::getModel()
{
    return model;
}

void IEC61850Tree::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);

    if (event->buttons() == Qt::LeftButton)
    {
        emit treeClicked(currentIndex());
    }
}
