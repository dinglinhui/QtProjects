#include <QHeaderView>
#include "examinationtable.h"

ExaminationTable::ExaminationTable(QWidget *parent) :
    QTableView(parent),
    m_pParent(parent),
    tableModel(new ProxyModel(this)),
    tablePopMenu(new QMenu(this)),
    printAction(new QAction(QIcon(":/res/images/256/print.png"), TRANSMIT_PRINT, this)),
    excelAction(new QAction(TRANSMIT_EXPORT_EXCEL, this)),
    csvAction(new QAction(TRANSMIT_EXPORT_CSV, this))
{
    tableModel->setDynamicSortFilter(true);
    tableModel->setSourceModel(createModel(this));
    this->setModel(tableModel);
    this->resizeRowsToContents();
    this->resizeColumnsToContents();
    this->setFocusPolicy(Qt::ClickFocus);
    //    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setAlternatingRowColors(true);
    this->horizontalHeader()->setStretchLastSection(true);
    this->setAutoScroll(true);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //水平滚动条按需显示
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setColumnWidth(INDEX_EXAMINATION_ID, 100);
    this->setColumnWidth(INDEX_EXAMINATION_DATE, 150);
    this->setColumnWidth(INDEX_EXAMINATION_STATUS, 100);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTableCustomContextMenuRequested(QPoint)));
}

ExaminationTable::~ExaminationTable()
{
    m_pParent = nullptr;
}

QAbstractItemModel *ExaminationTable::createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, INDEX_EXAMINATION_MAX_NUM, parent);

    model->setHeaderData(INDEX_EXAMINATION_ID, Qt::Horizontal, STRING_EXAMINATION_ID);
    model->setHeaderData(INDEX_EXAMINATION_DATE, Qt::Horizontal, STRING_EXAMINATION_DATE);
    model->setHeaderData(INDEX_EXAMINATION_STATUS, Qt::Horizontal, STRING_EXAMINATION_STATUS);
    model->setHeaderData(INDEX_EXAMINATION_NAME, Qt::Horizontal, STRING_EXAMINATION_NAME);

    return model;
}

void ExaminationTable::fillModel(const QList<QStringList> &exams)
{
    std::for_each(std::begin(exams), std::end(exams), [&](QStringList exam){
        int arow = tableModel->rowCount();
        tableModel->insertRow(arow);
        tableModel->setData(tableModel->index(arow, INDEX_EXAMINATION_ID), exam.at(INDEX_EXAMINATION_ID));
        tableModel->setData(tableModel->index(arow, INDEX_EXAMINATION_DATE), exam.at(INDEX_EXAMINATION_DATE));
        tableModel->setData(tableModel->index(arow, INDEX_EXAMINATION_STATUS), table_exam_status[exam.at(INDEX_EXAMINATION_STATUS).toInt()]);
        tableModel->setData(tableModel->index(arow, INDEX_EXAMINATION_NAME), exam.at(INDEX_EXAMINATION_NAME));
    });
}

void ExaminationTable::onTableCustomContextMenuRequested(QPoint pos)
{
    tablePopMenu->addAction(printAction);
    tablePopMenu->addSeparator();
    tablePopMenu->addAction(excelAction);
    tablePopMenu->addAction(csvAction);

    tablePopMenu->exec(QCursor::pos());
}
