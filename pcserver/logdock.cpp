#include <QAction>
#include <QHeaderView>
#include <QDateTime>
#include <QStandardItemModel>
#include "logdock.h"

LogDock::LogDock(const QString &title, QWidget *parent) :
    QDockWidget(title, parent),
    //    m_pLogTxt(new QTextEdit(this)),
    m_pTableView(new QTableView(this)),
    m_pModel(new ProxyModel(this))
{
    //    this->setWidget(m_pLogTxt);
    m_pModel->setSourceModel(createModel(this));
    m_pTableView->setModel(m_pModel);
    m_pTableView->resizeRowsToContents();
    m_pTableView->resizeColumnsToContents();
    m_pTableView->setFocusPolicy(Qt::ClickFocus);
    m_pTableView->setAlternatingRowColors(true);
    m_pTableView->horizontalHeader()->setStretchLastSection(true);
    m_pTableView->setAutoScroll(true);
    m_pTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //水平滚动条按需显示
    m_pTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_pTableView->setColumnWidth(LOG_DATE, 200);

    this->setWidget(m_pTableView);
}

LogDock::~LogDock()
{

}

QAbstractItemModel * LogDock::createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, LOG_MAX_NUM, parent);

    model->setHeaderData(LOG_DATE, Qt::Horizontal, LOGPRINT_DATE);
    model->setHeaderData(LOG_CONTEXT, Qt::Horizontal, LOGPRINT_CONTEXT);

    return model;
}

void LogDock::appendLog(const QString context)
{
    QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss zzz"); //设置显示格式

    int index = m_pModel->rowCount();
    m_pModel->insertRow(index);
    m_pModel->setData(m_pModel->index(index, LOG_DATE), timeStr);
    m_pModel->setData(m_pModel->index(index, LOG_CONTEXT), context);
    m_pTableView->scrollToBottom();
}
