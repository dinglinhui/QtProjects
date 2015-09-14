/*
 * iec61850tab.cpp
 *
 *  Created on: 2014年2月25日
 *      Author: dinglinhui
 */

#include "iec61850tab.h"

#include <QtGui>
#include <QSplitter>
#include <QHeaderView>
#include "pcdefs.h"

IEC61850Tab::IEC61850Tab(int nTabIndex, QWidget *parent) :
        PCTab(nTabIndex, parent)
{
    //
    proxyModel = new PCModel(this);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setSourceModel(createModel(this));
    //
    tableView = new QTableView;
    tableView->setModel(proxyModel);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
    tableView->setFocusPolicy(Qt::ClickFocus);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setAlternatingRowColors(true);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setAutoScroll(true);
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //水平滚动条按需显示
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    tableView->setColumnWidth(TABLE_COMMPKT_MASTER, 100);
    tableView->setColumnWidth(TABLE_COMMPKT_SEND_RECV, 50);
    tableView->setColumnWidth(TABLE_COMMPKT_TIME, 200);

    masterTree = new IEC61850Tree();
    masterTree->setSelectionBehavior(QAbstractItemView::SelectItems);
    masterTree->setSelectionMode(QAbstractItemView::SingleSelection);
    masterTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    masterTree->header()->hide();
    masterTree->expandAll();
//
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(masterTree);
    splitter->addWidget(tableView);
    splitter->setStretchFactor(0, 20);
    splitter->setStretchFactor(1, 80);

    layout = new BorderLayout;
    layout->addWidget(splitter, BorderLayout::Center);
    setLayout(layout);
}

void IEC61850Tab::masterFilterChanged(const QString & master)
{
    QRegExp regExp(master);
    proxyModel->setFilterRegExp(regExp);
}

QAbstractItemModel *IEC61850Tab::createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, TABLE_COMMPKT_MAX_NUM, parent);

    model->setHeaderData(TABLE_COMMPKT_MASTER, Qt::Horizontal, COMMPKT_MASTER);
    model->setHeaderData(TABLE_COMMPKT_SEND_RECV, Qt::Horizontal, COMMPKT_SEND_RECV);
    model->setHeaderData(TABLE_COMMPKT_TIME, Qt::Horizontal, COMMPKT_TIME);
    model->setHeaderData(TABLE_COMMPKT_PACKET, Qt::Horizontal, COMMPKT_PACKET);

    return model;
}

PCModel *IEC61850Tab::getModel()
{
    return proxyModel;
}

