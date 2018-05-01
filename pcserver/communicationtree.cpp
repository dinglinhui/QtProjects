#include <QModelIndex>
#include <QHeaderView>
#include <QDebug>
#include "communicationtree.h"
#include "pcdefs.h"

CommunicationTree::CommunicationTree(QWidget *parent) :
    QTreeView(parent),
    treeModel(new QStandardItemModel(1, 1)),
    communication(new QStandardItem(COMMUNICATION_MANAGE)),
    treePopMenu(new QMenu(this)),
    callAction(new QAction(QIcon(":/res/images/256/reload.png"), COMMUNICATION_CALL, this)) {
    communication->setIcon(QIcon(":/res/images/256/aim.png"));
    treeModel->setHeaderData(0, Qt::Horizontal, COMMUNICATION_MANAGE);
    treeModel->setItem(0, 0, communication);

    this->setModel(treeModel);
    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->header()->hide();
    this->expandAll();
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTreeCustomContextMenuRequested(QPoint)));
}

CommunicationTree::~CommunicationTree() {

}

QString CommunicationTree::getCurrentItemName() {
    QString name;
    return getCurrentItemName(name);
}

QString CommunicationTree::getCurrentItemName(QString &name) {
    QModelIndex index = this->currentIndex();

    name = treeModel->data(index).toString();
    return treeModel->data(index).toString();
}

QString CommunicationTree::getCurrentItemFullName(QString &name) {
    QModelIndex index = this->currentIndex();

    if(index.parent().parent().row() == 0) {//具体某个通道index.parent()的某个转发表index召唤
        name = treeModel->data(index.parent()).toString().append("_").append(treeModel->data(index).toString());
        return name;
    } else {//具体某个通道index召唤
        name = treeModel->data(index).toString();
        return name;
    }
}

void CommunicationTree::insertItems(const QString &text, int linkIndex) {
    insertTransmitItems(text, linkIndex);
}

void CommunicationTree::insertItems(const int socketDescriptor, const QString & ip, const quint16 /*port*/, int linkIndex) {
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
    communication->appendRow(item);
}

void CommunicationTree::insertTransmitItems(const QString &text, int linkIndex) {
    QStandardItem *item = new QStandardItem(text);

    if(linkIndex == LINKINFO_CONNECTED)
        item->setIcon(QIcon(":/res/images/256/ligthbulb_on.png"));
    else
        item->setIcon(QIcon(":/res/images/256/ligthbulb_off.png"));
    communication->appendRow(item);

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

void CommunicationTree::removeItems(const QString &text) {
    QList<QStandardItem *> list = this->returnTheItems(text);
    std::for_each(std::begin(list), std::end(list), [this](QStandardItem *item) {
        communication->removeRow(item->row());
    });
}

void CommunicationTree::removeTransmitItems(const QString &, int) {

}

void CommunicationTree::changeItems(const QString &text, int linkIndex) {
    QList<QStandardItem *> list = this->returnTheItems(text);
    std::for_each(std::begin(list), std::end(list), [linkIndex](QStandardItem *item){
        if(linkIndex == LINKINFO_CONNECTED)
            item->setIcon(QIcon(":/res/images/256/ligthbulb_on.png"));
        else
            item->setIcon(QIcon(":/res/images/256/ligthbulb_off.png"));
    });
}

bool CommunicationTree::searchItems(const QString &text) {
    QList<QStandardItem *> list = this->returnTheItems(text);
    if (list.isEmpty()) {
        return false;
    }

    return true;
}

bool CommunicationTree::searchItems(const QString &text, Qt::MatchFlags flags) {
    QList<QStandardItem *> list = this->returnTheItems(text, flags);
    if (list.isEmpty()) {
        return false;
    }

    return true;
}

void CommunicationTree::clearItems() {
    treeModel->removeRows(0, treeModel->rowCount(), communication->index());
    communication->setRowCount(0);
}

QList<QStandardItem *> CommunicationTree::returnTheItems() {
    return treeModel->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> CommunicationTree::returnTheItems(const QString &text) {
    return treeModel->findItems(text, Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> CommunicationTree::returnTheItems(const QString &text, Qt::MatchFlags flags) {
    return treeModel->findItems(text, flags);
}

QStandardItemModel *CommunicationTree::getModel() {
    return treeModel;
}

void CommunicationTree::mousePressEvent(QMouseEvent *event) {
    QTreeView::mousePressEvent(event);

    if (event->buttons() == Qt::LeftButton) {
        emit treeClicked(currentIndex());
    }
}

void CommunicationTree::onTreeCustomContextMenuRequested(QPoint) {
    treePopMenu->addAction(callAction);

    treePopMenu->exec(QCursor::pos());
}
