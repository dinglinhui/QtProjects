#include <QModelIndex>
#include <QDebug>
#include "transmittree.h"
#include "pcdefs.h"

TransmitTree::TransmitTree(QWidget *parent) :
    QTreeView(parent)
{
    treeModel = new QStandardItemModel(1, 1);
    treeModel->setHeaderData(0, Qt::Horizontal, TRANSMIT_MASTER);
    //
    transmit = new QStandardItem(TRANSMIT_MASTER);
    transmit->setIcon(QIcon(":/res/images/256/aim.png"));
    treeModel->setItem(0, 0, transmit);
    //
    soebuffer = new QStandardItem(SOE_BUFFER);
    soebuffer->setIcon(QIcon(":/res/images/256/antenna2.png"));
    treeModel->setItem(1, 0, soebuffer);

    this->setModel(treeModel);
}

QString TransmitTree::getCurrentItemName()
{
    QString name;
    return getCurrentItemName(name);
}

QString TransmitTree::getCurrentItemName(QString &name)
{
    QModelIndex index = this->currentIndex();

    name = treeModel->data(index).toString();
    return treeModel->data(index).toString();
}

QString TransmitTree::getCurrentItemFullName(QString &name)
{
    QModelIndex index = this->currentIndex();

    if(index.parent().parent().row() == 0)//具体某个通道index.parent()的某个转发表index召唤
    {
        name = treeModel->data(index.parent()).toString().append("_").append(treeModel->data(index).toString());
        return name;
    }
    else//具体某个通道index召唤
    {
        name = treeModel->data(index).toString();
        return name;
    }
}

void TransmitTree::insertItems(const QString &text, int linkIndex)
{
    insertTransmitItems(text, linkIndex);
}

void TransmitTree::insertItems(const int socketDescriptor, const QString & ip, const quint16 port, int linkIndex)
{
//    QList<QStandardItem*> list;
//    list.append(new QStandardItem(QString(socketDescriptor)));
//    list.append(new QStandardItem(ip));
//    list.append(new QStandardItem(QString(port)));
//    QString channelInfo = QStringLiteral("%1(%2):%3").arg(ip).arg(socketDescriptor).arg(port);

    QStandardItem *item = new QStandardItem(QStringLiteral("%1(%2)").arg(ip).arg(socketDescriptor));
    if(linkIndex == LINKINFO_CONNECTED)
        item->setIcon(QIcon(":/res/images/256/ligthbulb_on.png"));
    else
        item->setIcon(QIcon(":/res/images/256/ligthbulb_off.png"));
    transmit->appendRow(item);
}

void TransmitTree::insertTransmitItems(const QString &text, int linkIndex)
{
    QStandardItem *item = new QStandardItem(text);

    if(linkIndex == LINKINFO_CONNECTED)
        item->setIcon(QIcon(":/res/images/256/ligthbulb_on.png"));
    else
        item->setIcon(QIcon(":/res/images/256/ligthbulb_off.png"));
    transmit->appendRow(item);

    //    QStandardItem *secondItem1 = new QStandardItem(QStringLiteral("YC"));
    //    secondItem1->setIcon(QIcon(":/res/images/Orange Ball.png"));
    //    firstItem->appendRow(secondItem1);

    //    QStandardItem *secondItem2 = new QStandardItem(QStringLiteral("YX"));
    //    secondItem2->setIcon(QIcon(":/res/images/Green Ball.png"));
    //    firstItem->appendRow(secondItem2);

    //    QStandardItem *secondItem3 = new QStandardItem(QStringLiteral("YK"));
    //    secondItem3->setIcon(QIcon(":/res/images/Yellow Ball.png"));
    //    firstItem->appendRow(secondItem3);
}

void TransmitTree::removeItems(const QString &text)
{
    QList<QStandardItem *> list = this->returnTheItems(text);
    std::for_each(std::begin(list), std::end(list), [this](QStandardItem *item){
        transmit->removeRow(item->row());
    });
}

void TransmitTree::removeTransmitItems(const QString &text, int linkIndex)
{

}

void TransmitTree::changeItems(const QString &text, int linkIndex)
{
    QList<QStandardItem *> list = this->returnTheItems(text);
    std::for_each(std::begin(list), std::end(list), [linkIndex](QStandardItem *item){
        if(linkIndex == LINKINFO_CONNECTED)
            item->setIcon(QIcon(":/res/images/256/ligthbulb_on.png"));
        else
            item->setIcon(QIcon(":/res/images/256/ligthbulb_off.png"));
    });
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

bool TransmitTree::searchItems(const QString &text, Qt::MatchFlags flags)
{
    QList<QStandardItem *> list = this->returnTheItems(text, flags);
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
        treeModel->removeRows(0, treeModel->rowCount(), transmit->index());
        transmit->setRowCount(0);
    }
    else
    {
        treeModel->removeRows(0, treeModel->rowCount(), soebuffer->index());
        soebuffer->setRowCount(0);
    }
}

QList<QStandardItem *> TransmitTree::returnTheItems()
{
    return treeModel->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> TransmitTree::returnTheItems(const QString &text)
{
    return treeModel->findItems(text, Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> TransmitTree::returnTheItems(const QString &text, Qt::MatchFlags flags)
{
    return treeModel->findItems(text, flags);
}

QStandardItemModel *TransmitTree::getModel()
{
    return treeModel;
}

void TransmitTree::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);

    if (event->buttons() == Qt::LeftButton)
    {
        emit treeClicked(currentIndex());
    }
}
