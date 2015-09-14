/*
 * IEC103Tree.cpp
 *
 *  Created on: 2014年2月26日
 *      Author: dinglinhui
 */

#include <QModelIndex>
#include <QDebug>
#include "iec103tree.h"
#include "pcdefs.h"

IEC103Tree::IEC103Tree(QWidget *parent) :
        QTreeView(parent)
{
    model = new QStandardItemModel(1, 1);
    model->setHeaderData(0, Qt::Horizontal, COMMUNICATION_MASTER);
    //
    root = new QStandardItem(COMMUNICATION_MASTER);
    root->setIcon(QIcon(":/system/images/256/shield.png"));
    model->setItem(0, 0, root);

    this->setModel(model);
}

IEC103Tree::~IEC103Tree()
{

}

QString IEC103Tree::getCurrentItemName()
{
    QString name;
    return getCurrentItemName(name);
}

QString IEC103Tree::getCurrentItemName(QString &name)
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

void IEC103Tree::insertItems(const QString &text)
{
    insertItems(root, text);
}

void IEC103Tree::insertItems(QStandardItem *item, const QString &text)
{
    QStandardItem *item1 = new QStandardItem(text);
    item1->setIcon(QIcon(":/system/images/tag_blue.png"));
    item->appendRow(item1);
}

bool IEC103Tree::searchItems(const QString &text)
{
    QList<QStandardItem *> list = this->returnTheItems(text);
    if (list.isEmpty())
    {
        return false;
    }

    return true;
}

QList<QStandardItem *> IEC103Tree::returnTheItems()
{
    return model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> IEC103Tree::returnTheItems(const QString &text)
{
    return model->findItems(text, Qt::MatchWildcard | Qt::MatchRecursive);
}

QStandardItemModel *IEC103Tree::getModel()
{
    return model;
}

void IEC103Tree::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);

    if (event->buttons() == Qt::LeftButton)
    {
        emit treeClicked(currentIndex());
    }
}
