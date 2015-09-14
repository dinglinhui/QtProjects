#include <QModelIndex>
#include <QDebug>
#include "transmittree.h"
#include "pcdefs.h"

TransmitTree::TransmitTree(QWidget *parent) :
    QTreeView(parent)
{
    model = new QStandardItemModel(1, 1);
    model->setHeaderData(0, Qt::Horizontal, TRANSMIT_MASTER);
    //
    transmit = new QStandardItem(TRANSMIT_MASTER);
    transmit->setIcon(QIcon(":/system/images/256/aim.png"));
    model->setItem(0, 0, transmit);
    //
    soebuffer = new QStandardItem(SOE_BUFFER);
    soebuffer->setIcon(QIcon(":/system/images/256/antenna2.png"));
    model->setItem(1, 0, soebuffer);

    this->setModel(model);
}

QString TransmitTree::getCurrentItemName()
{
    QString name;
    return getCurrentItemName(name);
}

QString TransmitTree::getCurrentItemName(QString &name)
{
    QModelIndex index = this->currentIndex();

    name = model->data(index).toString();
    return model->data(index).toString();
}

QString TransmitTree::getCurrentItemFullName(QString &name)
{
    QModelIndex index = this->currentIndex();

    /*if((index.parent().parent().row() == -1)&&(index.parent().row() == -1))//转发通道
    {

    }
    else */if(index.parent().parent().row() == 0)//具体某个通道index.parent()的某个转发表index召唤
    {
        name = model->data(index.parent()).toString().append("_").append(model->data(index).toString());
        return name;
    }
    else// if((index.parent().parent().row() == -1)&&(index.parent().row() == 0))//具体某个通道index召唤
    {
        name = model->data(index).toString();
        return name;
    }
}

void TransmitTree::insertItems(int typeIndex, int chnlindex, int iedindex, const QString &text)
{
    if(typeIndex == TRANSINFO_TRANSMIT)
        insertTransmitItems(text);
    else
        insertSoeBufferItems(chnlindex, iedindex, text);
}

void TransmitTree::insertTransmitItems(const QString &text)
{
    QStandardItem *firstItem = new QStandardItem(text);
    firstItem->setIcon(QIcon(":/system/images/256/ligthbulb_on.png"));
    transmit->appendRow(firstItem);

    QStandardItem *secondItem1 = new QStandardItem(QStringLiteral("遥测"));
    secondItem1->setIcon(QIcon(":/system/images/Orange Ball.png"));
    firstItem->appendRow(secondItem1);

    QStandardItem *secondItem2 = new QStandardItem(QStringLiteral("遥信"));
    secondItem2->setIcon(QIcon(":/system/images/Green Ball.png"));
    firstItem->appendRow(secondItem2);

    QStandardItem *secondItem3 = new QStandardItem(QStringLiteral("遥控"));
    secondItem3->setIcon(QIcon(":/system/images/Yellow Ball.png"));
    firstItem->appendRow(secondItem3);
}

void TransmitTree::insertSoeBufferItems(int chnlindex, int iedindex, const QString &text)
{
    if(iedindex == 0)//通道
    {
        QStandardItem *firstItem = new QStandardItem(text);
        firstItem->setIcon(QIcon(":/system/images/256/ligthbulb_on.png"));
        soebuffer->appendRow(firstItem);
    }
    else//装置
    {
        QStandardItem *iedItem = new QStandardItem(text);
        iedItem->setIcon(QIcon(":/system/images/Blue Ball.png"));
        soebuffer->child(chnlindex)->appendRow(iedItem);
    }
}

bool TransmitTree::searchItems(const QString &text)
{
    QList<QStandardItem *> list = this->returnTheItems(text);
    if (list.isEmpty())
    {
        return false;
    }

    return true;
}

void TransmitTree::clearItems(int typeIndex)
{
    if(typeIndex == TRANSINFO_TRANSMIT)
    {
        model->removeRows(0, model->rowCount(), transmit->index());
        transmit->setRowCount(0);
    }
    else
    {
        model->removeRows(0, model->rowCount(), soebuffer->index());
        soebuffer->setRowCount(0);
    }
}

QList<QStandardItem *> TransmitTree::returnTheItems()
{
    return model->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> TransmitTree::returnTheItems(const QString &text)
{
    return model->findItems(text, Qt::MatchWildcard | Qt::MatchRecursive);
}

QStandardItemModel *TransmitTree::getModel()
{
    return model;
}

void TransmitTree::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);

    if (event->buttons() == Qt::LeftButton)
    {
        emit treeClicked(currentIndex());
    }
}
