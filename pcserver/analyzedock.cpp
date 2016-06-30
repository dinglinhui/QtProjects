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
//    m_pTableView->setRowHeight(TABLE_COMMPKT_PACKET, 200);

    this->setWidget(m_pTableView);
}

AnalyzeDock::~AnalyzeDock()
{

}

QAbstractItemModel * AnalyzeDock::createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, INDEX_EXAMINATION_MAX_NUM, parent);

    model->setHeaderData(INDEX_EXAMINATION_ID, Qt::Horizontal, STRING_EXAMINATION_ID);
    model->setHeaderData(INDEX_EXAMINATION_DATE, Qt::Horizontal, STRING_EXAMINATION_DATE);
    model->setHeaderData(INDEX_EXAMINATION_STATUS, Qt::Horizontal, STRING_EXAMINATION_STATUS);
    model->setHeaderData(INDEX_EXAMINATION_NAME, Qt::Horizontal, STRING_EXAMINATION_NAME);

    return model;
}
