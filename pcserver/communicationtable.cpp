#include <QHeaderView>
#include "communicationtable.h"

CommunicationTable::CommunicationTable(QWidget *parent) :
    QTableView(parent),
    tableModel(new ProxyModel(this)),
    tablePopMenu(new QMenu(this)),
    printAction(new QAction(QIcon(":/res/images/256/print.png"), TRANSMIT_PRINT, this)),
    excelAction(new QAction(TRANSMIT_EXPORT_EXCEL, this)),
    csvAction(new QAction(TRANSMIT_EXPORT_CSV, this)) {

    tableModel->setDynamicSortFilter(true);
    tableModel->setSourceModel(createModel(this));
    this->setModel(tableModel);
    this->resizeRowsToContents();
    this->resizeColumnsToContents();
    this->setFocusPolicy(Qt::ClickFocus);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setAlternatingRowColors(true);
    this->horizontalHeader()->setStretchLastSection(true);
    this->setAutoScroll(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //水平滚动条按需显示
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setColumnWidth(INDEX_COMMUNICATION_ID, 100);
    this->setColumnWidth(INDEX_COMMUNICATION_NAME, 150);
    this->setColumnWidth(INDEX_COMMUNICATION_DATETIME, 150);
    this->setColumnWidth(INDEX_COMMUNICATION_DIRECTION, 100);
//    this->setColumnWidth(INDEX_COMMUNICATION_DIRECTION, 100);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTableCustomContextMenuRequested(QPoint)));
}

CommunicationTable::~CommunicationTable() {

}

QAbstractItemModel *CommunicationTable::createModel(QObject *parent) {
    QStandardItemModel *model = new QStandardItemModel(0, INDEX_COMMUNICATION_MAX_NUM, parent);

    model->setHeaderData(INDEX_COMMUNICATION_ID, Qt::Horizontal, STRING_COMMUNICATION_ID);
    model->setHeaderData(INDEX_COMMUNICATION_NAME, Qt::Horizontal, STRING_COMMUNICATION_NAME);
    model->setHeaderData(INDEX_COMMUNICATION_DATETIME, Qt::Horizontal, STRING_COMMUNICATION_DATETIME);
    model->setHeaderData(INDEX_COMMUNICATION_DIRECTION, Qt::Horizontal, STRING_COMMUNICATION_DIRECTION);
    model->setHeaderData(INDEX_COMMUNICATION_CONTENT, Qt::Horizontal, STRING_COMMUNICATION_CONTENT);

    return model;
}

void CommunicationTable::onTableCustomContextMenuRequested(QPoint pos) {
    tablePopMenu->addAction(printAction);
    tablePopMenu->addSeparator();
    tablePopMenu->addAction(excelAction);
    tablePopMenu->addAction(csvAction);

    tablePopMenu->exec(QCursor::pos());
}
