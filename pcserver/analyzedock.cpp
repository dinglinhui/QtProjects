#include <QStandardItemModel>
#include <QHeaderView>
#include "analyzedock.h"

AnalyzeDock::AnalyzeDock(const QString &title, QWidget *parent):
    QDockWidget(title, parent),
    m_pTableView(new QTableView(this)),
    m_pModel(new ProxyModel(this))
{
    m_pModel->setSourceModel(createModel(this));
    m_pTableView->setModel(m_pModel);
    m_pTableView->horizontalHeader()->hide();
    m_pTableView->horizontalHeader()->setStretchLastSection(true);
    m_pTableView->verticalHeader()->setStretchLastSection(true);
    m_pTableView->setRowHeight(TABLE_COMMPKT_PACKET, 200);

    this->setWidget(m_pTableView);
}

AnalyzeDock::~AnalyzeDock()
{

}

QAbstractItemModel * AnalyzeDock::createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(TABLE_COMMPKT_MAX_NUM + 1, 0, parent);

    model->setHeaderData(TABLE_COMMPKT_MASTER, Qt::Vertical, COMMPKT_MASTER);
    model->setHeaderData(TABLE_COMMPKT_SEND_RECV, Qt::Vertical,COMMPKT_SEND_RECV);
    model->setHeaderData(TABLE_COMMPKT_TIME, Qt::Vertical, COMMPKT_TIME);
    model->setHeaderData(TABLE_COMMPKT_PACKET, Qt::Vertical, COMMPKT_PACKET);
    //
    model->setHeaderData(TABLE_COMMPKT_PACKET_ANALYZE, Qt::Vertical,COMMPKT_PACKET_ANALYZE);

    return model;
}
