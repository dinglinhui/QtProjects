#include <QModelIndex>
#include <QHeaderView>
#include <QDebug>
#include "graphtree.h"
#include "pcdefs.h"

GraphTree::GraphTree(QWidget *parent) :
    QTreeView(parent),
    treeModel(new QStandardItemModel(1, 1)),
    graph(new QStandardItem(GRAPH_CONTROL)),
    treePopMenu(new QMenu(this)),
    callAction(new QAction(QIcon(":/res/images/256/reload.png"), GRAPH_CONTROL, this)) {
    graph->setIcon(QIcon(":/res/images/256/aim.png"));
    treeModel->setHeaderData(0, Qt::Horizontal, GRAPH_CONTROL);
    treeModel->setItem(0, 0, graph);

    this->setModel(treeModel);
    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->header()->hide();
    this->expandAll();
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTreeCustomContextMenuRequested(QPoint)));
}

GraphTree::~GraphTree() {

}

QString GraphTree::getCurrentItemName() {
    QString name;
    return getCurrentItemName(name);
}

QString GraphTree::getCurrentItemName(QString &name) {
    QModelIndex index = this->currentIndex();

    name = treeModel->data(index).toString();
    return treeModel->data(index).toString();
}

QString GraphTree::getCurrentItemFullName(QString &name) {
    QModelIndex index = this->currentIndex();

    if(index.parent().parent().row() == 0) {//具体某个通道index.parent()的某个转发表index召唤
        name = treeModel->data(index.parent()).toString().append("_").append(treeModel->data(index).toString());
        return name;
    } else {//具体某个通道index召唤
        name = treeModel->data(index).toString();
        return name;
    }
}

void GraphTree::insertItems(const QString &text, int linkIndex) {
    insertTransmitItems(text, linkIndex);
}

void GraphTree::insertItems(const int socketDescriptor, const QString & ip, const quint16 port, int linkIndex) {
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
    graph->appendRow(item);
}

void GraphTree::insertTransmitItems(const QString &text, int linkIndex) {
    QStandardItem *item = new QStandardItem(text);

    if(linkIndex == LINKINFO_CONNECTED)
        item->setIcon(QIcon(":/res/images/256/ligthbulb_on.png"));
    else
        item->setIcon(QIcon(":/res/images/256/ligthbulb_off.png"));
    graph->appendRow(item);

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

void GraphTree::removeItems(const QString &text) {
    QList<QStandardItem *> list = this->returnTheItems(text);
    std::for_each(std::begin(list), std::end(list), [this](QStandardItem *item) {
        graph->removeRow(item->row());
    });
}

void GraphTree::removeTransmitItems(const QString &text, int linkIndex) {

}

void GraphTree::changeItems(const QString &text, int linkIndex) {
    QList<QStandardItem *> list = this->returnTheItems(text);
    std::for_each(std::begin(list), std::end(list), [linkIndex](QStandardItem *item){
        if(linkIndex == LINKINFO_CONNECTED)
            item->setIcon(QIcon(":/res/images/256/ligthbulb_on.png"));
        else
            item->setIcon(QIcon(":/res/images/256/ligthbulb_off.png"));
    });
}

bool GraphTree::searchItems(const QString &text) {
    QList<QStandardItem *> list = this->returnTheItems(text);
    if (list.isEmpty()) {
        return false;
    }

    return true;
}

bool GraphTree::searchItems(const QString &text, Qt::MatchFlags flags) {
    QList<QStandardItem *> list = this->returnTheItems(text, flags);
    if (list.isEmpty()) {
        return false;
    }

    return true;
}

void GraphTree::clearItems() {
    treeModel->removeRows(0, treeModel->rowCount(), graph->index());
    graph->setRowCount(0);
}

QList<QStandardItem *> GraphTree::returnTheItems() {
    return treeModel->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> GraphTree::returnTheItems(const QString &text) {
    return treeModel->findItems(text, Qt::MatchWildcard | Qt::MatchRecursive);
}

QList<QStandardItem *> GraphTree::returnTheItems(const QString &text, Qt::MatchFlags flags) {
    return treeModel->findItems(text, flags);
}

QStandardItemModel *GraphTree::getModel() {
    return treeModel;
}

void GraphTree::mousePressEvent(QMouseEvent *event) {
    QTreeView::mousePressEvent(event);

    if (event->buttons() == Qt::LeftButton) {
        emit treeClicked(currentIndex());
    }
}

void GraphTree::onTreeCustomContextMenuRequested(QPoint pos) {
    treePopMenu->addAction(callAction);

    treePopMenu->exec(QCursor::pos());
}
