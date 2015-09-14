#include <QtCore>
#include <QtGui>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QProgressDialog>
#include <QApplication>

#include "transmitwidget.h"
#include "pcdefs.h"

#include "xlsxdocument.h"
#include "xlsxformat.h"
#include "xlsxcellrange.h"
#include "xlsxworksheet.h"

QTXLSX_USE_NAMESPACE

TransmitWidget::TransmitWidget(QWidget *parent) :
    QWidget(parent),
    treePopMenu(new QMenu(this)),
    tablePopMenu(new QMenu(this)),
    callAction(new QAction(QIcon(":/res/images/256/reload.png"), TRANSMIT_CALL, this)),
    printAction(new QAction(QIcon(":/res/images/256/print.png"), TRANSMIT_PRINT, this)),
    excelAction(new QAction(TRANSMIT_EXPORT_EXCEL, this)),
    csvAction(new QAction(TRANSMIT_EXPORT_CSV, this)),
    m_pPrinter(new QPrinter()),
    m_nChnlIndex(0),
    m_nIedIndex(0),
    m_nTypeIndex(0)
{
    connect(callAction, SIGNAL(triggered()), this, SLOT(onCallTriggered()));
    connect(printAction, SIGNAL(triggered()), this, SLOT(printTransmit()));
    connect(excelAction, SIGNAL(triggered()), this, SLOT(onExportExcelTriggered()));
    connect(csvAction, SIGNAL(triggered()), this, SLOT(onExportCsvTriggered()));

    for(int i=0;i<CHANNEL_MAX;i++)
    {
        //遥测
        m_pAIModel[i] = new ProxyModel(this);
        m_pAIModel[i]->setDynamicSortFilter(true);
        m_pAIModel[i]->setSourceModel(createAIModel(this));
        //遥信
        m_pCOSModel[i] = new ProxyModel(this);
        m_pCOSModel[i]->setDynamicSortFilter(true);
        m_pCOSModel[i]->setSourceModel(createCOSModel(this));
        //遥控
        m_pDOModel[i] = new ProxyModel(this);
        m_pDOModel[i]->setDynamicSortFilter(true);
        m_pDOModel[i]->setSourceModel(createDOModel(this));
        //SOE缓存
        for(int j=0;j<IED_MAX;j++)
        {
            m_pSoeBufferModel[i][j] = new ProxyModel(this);
            m_pSoeBufferModel[i][j]->setDynamicSortFilter(true);
            m_pSoeBufferModel[i][j]->setSourceModel(createSoeBufferModel(this));
        }
    }
    //
    transmitTable = new TransmitTable();
    transmitTable->setModel(m_pAIModel[0]);
    transmitTable->resizeRowsToContents();
    transmitTable->resizeColumnsToContents();
    transmitTable->setFocusPolicy(Qt::ClickFocus);
    transmitTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    transmitTable->setAlternatingRowColors(true);
    transmitTable->horizontalHeader()->setStretchLastSection(true);
    transmitTable->setAutoScroll(true);
    transmitTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //水平滚动条按需显示
    transmitTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    transmitTable->setSelectionMode(QAbstractItemView::SingleSelection);
    transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_INDEX, 80);
    transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_INFOADDR, 80);
    transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_IEDADDR, 80);
    transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_DESC, 400);
    transmitTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(transmitTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTableCustomContextMenuRequested(QPoint)));

    transmitTree = new TransmitTree();
    transmitTree->setSelectionBehavior(QAbstractItemView::SelectItems);
    transmitTree->setSelectionMode(QAbstractItemView::SingleSelection);
    transmitTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    transmitTree->header()->hide();
    transmitTree->expandAll();
    transmitTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(transmitTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTreeCustomContextMenuRequested(QPoint)));


    //
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(transmitTree);
    splitter->addWidget(transmitTable);
    splitter->setStretchFactor(0, 20);
    splitter->setStretchFactor(1, 80);

    BorderLayout *layout = new BorderLayout;
    layout->addWidget(splitter, BorderLayout::Center);
    this->setLayout(layout);
}

TransmitWidget::~TransmitWidget(void)
{
    if(m_pPrinter != nullptr)
        delete m_pPrinter, m_pPrinter = nullptr;
}

TransmitTree * TransmitWidget::getTransmitTree()
{
    return transmitTree;
}

TransmitTable * TransmitWidget::getTransmitTable()
{
    return transmitTable;
}

QAbstractItemModel *TransmitWidget::createAIModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, TABLE_TRANSMITINFO_AI_MAX_NUM, parent);

    model->setHeaderData(TABLE_TRANSMITINFO_AI_INDEX, Qt::Horizontal, TRANSMITINFO_INDEX);
    model->setHeaderData(TABLE_TRANSMITINFO_AI_INFOADDR, Qt::Horizontal, TRANSMITINFO_INFOADDR);
    model->setHeaderData(TABLE_TRANSMITINFO_AI_IEDADDR, Qt::Horizontal, TRANSMITINFO_IEDADDR);
    model->setHeaderData(TABLE_TRANSMITINFO_AI_DESC, Qt::Horizontal, TRANSMITINFO_DESC);
    model->setHeaderData(TABLE_TRANSMITINFO_AI_THRESHOLD_TYPE, Qt::Horizontal, TRANSMITINFO_THRESHOLD_TYPE);
    model->setHeaderData(TABLE_TRANSMITINFO_AI_THRESHOLD, Qt::Horizontal, TRANSMITINFO_THRESHOLD);
    model->setHeaderData(TABLE_TRANSMITINFO_AI_OFFSET, Qt::Horizontal, TRANSMITINFO_OFFSET);
    model->setHeaderData(TABLE_TRANSMITINFO_AI_MULTIFACTOR, Qt::Horizontal, TRANSMITINFO_MULTIFACTOR);

    return model;
}

QAbstractItemModel *TransmitWidget::createSoeBufferModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, TABLE_TRANSMITINFO_SOE_BUFFER_MAX_NUM, parent);

    model->setHeaderData(TABLE_TRANSMITINFO_SOE_BUFFER_TYPE, Qt::Horizontal, SOE_BUFFER_TYPE);
    model->setHeaderData(TABLE_TRANSMITINFO_SOE_BUFFER_INDEX, Qt::Horizontal, SOE_BUFFER_INDEX);
    model->setHeaderData(TABLE_TRANSMITINFO_SOE_BUFFER_OLDEST, Qt::Horizontal, SOE_BUFFER_OLDEST);
    model->setHeaderData(TABLE_TRANSMITINFO_SOE_BUFFER_DESC, Qt::Horizontal, SOE_BUFFER_DESC);
    model->setHeaderData(TABLE_TRANSMITINFO_SOE_BUFFER_VALUE, Qt::Horizontal, SOE_BUFFER_VALUE);
    model->setHeaderData(TABLE_TRANSMITINFO_SOE_BUFFER_QUALITY, Qt::Horizontal, SOE_BUFFER_QUALITY);
    model->setHeaderData(TABLE_TRANSMITINFO_SOE_BUFFER_TIME, Qt::Horizontal, SOE_BUFFER_TIME);

    return model;
}

QAbstractItemModel *TransmitWidget::createCOSModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, TABLE_TRANSMITINFO_COS_MAX_NUM, parent);

    model->setHeaderData(TABLE_TRANSMITINFO_COS_INDEX, Qt::Horizontal, TRANSMITINFO_INDEX);
    model->setHeaderData(TABLE_TRANSMITINFO_COS_INFOADDR, Qt::Horizontal, TRANSMITINFO_INFOADDR);
    model->setHeaderData(TABLE_TRANSMITINFO_COS_IEDADDR, Qt::Horizontal, TRANSMITINFO_IEDADDR);
    model->setHeaderData(TABLE_TRANSMITINFO_COS_DESC, Qt::Horizontal, TRANSMITINFO_DESC);
    model->setHeaderData(TABLE_TRANSMITINFO_COS_STATUSMODI, Qt::Horizontal, TRANSMITINFO_STATUSMODI);

    return model;
}

QAbstractItemModel *TransmitWidget::createDOModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, TABLE_TRANSMITINFO_DO_MAX_NUM, parent);

    model->setHeaderData(TABLE_TRANSMITINFO_DO_INDEX, Qt::Horizontal, TRANSMITINFO_INDEX);
    model->setHeaderData(TABLE_TRANSMITINFO_DO_INFOADDR, Qt::Horizontal, TRANSMITINFO_INFOADDR);
    model->setHeaderData(TABLE_TRANSMITINFO_DO_IEDADDR, Qt::Horizontal, TRANSMITINFO_IEDADDR);
    model->setHeaderData(TABLE_TRANSMITINFO_DO_DESC, Qt::Horizontal, TRANSMITINFO_DESC);

    return model;
}

void TransmitWidget::clearModel(int chnlIndex, int iedIndex, int typeIndex)
{
    if((chnlIndex<0)||(chnlIndex>CHANNEL_MAX))
    {
        qDebug() << chnlIndex << iedIndex << typeIndex;
        return;
    }

    if((iedIndex<0)||(iedIndex>IED_MAX))
    {
        qDebug() << chnlIndex << iedIndex << typeIndex;
        return;
    }

    switch(typeIndex)
    {
    case TRANSMIT_CHNL_S:
    {
        if (m_pAIModel[chnlIndex]->rowCount() > 0)
        {
            m_pAIModel[chnlIndex]->removeRows(0, m_pAIModel[chnlIndex]->rowCount());
        }

        if (m_pCOSModel[chnlIndex]->rowCount() > 0)
        {
            m_pCOSModel[chnlIndex]->removeRows(0, m_pCOSModel[chnlIndex]->rowCount());
        }

        if (m_pDOModel[chnlIndex]->rowCount() > 0)
        {
            m_pDOModel[chnlIndex]->removeRows(0, m_pDOModel[chnlIndex]->rowCount());
        }
        break;
    }
    case TRANSMIT_AI:
    {
        if (m_pAIModel[chnlIndex]->rowCount() > 0)
        {
            m_pAIModel[chnlIndex]->removeRows(0, m_pAIModel[chnlIndex]->rowCount());
        }
        break;
    }
    case TRANSMIT_COS:
    {
        if (m_pCOSModel[chnlIndex]->rowCount() > 0)
        {
            m_pCOSModel[chnlIndex]->removeRows(0, m_pCOSModel[chnlIndex]->rowCount());
        }
        break;
    }
    case TRANSMIT_DO:
    {
        if (m_pDOModel[chnlIndex]->rowCount() > 0)
        {
            m_pDOModel[chnlIndex]->removeRows(0, m_pDOModel[chnlIndex]->rowCount());
        }
        break;
    }
    case SOE_BUFFER_DATA:
    {
        if (m_pSoeBufferModel[chnlIndex][iedIndex]->rowCount() > 0)
        {
            m_pSoeBufferModel[chnlIndex][iedIndex]->removeRows(0, m_pSoeBufferModel[chnlIndex][iedIndex]->rowCount());
        }
        break;
    }
    default:
        break;
    }
}

void TransmitWidget::changeModel(int chnlIndex, int iedIndex, int typeIndex)
{
    m_nChnlIndex = chnlIndex;
    m_nIedIndex = iedIndex;
    m_nTypeIndex = typeIndex;
    switch(m_nTypeIndex)
    {
    case TRANSMIT_AI:
    case TRANSMIT_CHNL_S:
    {
        transmitTable->setModel(m_pAIModel[m_nChnlIndex]);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_INDEX, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_INFOADDR, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_IEDADDR, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_DESC, 400);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_THRESHOLD_TYPE, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_THRESHOLD, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_AI_OFFSET, 80);
        break;
    }
    case TRANSMIT_COS:
    {
        transmitTable->setModel(m_pCOSModel[m_nChnlIndex]);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_COS_INDEX, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_COS_INFOADDR, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_COS_IEDADDR, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_COS_DESC, 400);
        break;
    }
    case TRANSMIT_DO:
    {
        transmitTable->setModel(m_pDOModel[m_nChnlIndex]);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_DO_INDEX, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_DO_INFOADDR, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_DO_IEDADDR, 80);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_DO_DESC, 400);
        break;
    }
    case SOE_BUFFER_CHNL:
    {
        transmitTable->setModel(m_pSoeBufferModel[m_nChnlIndex][m_nIedIndex]);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_SOE_BUFFER_TYPE, 60);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_SOE_BUFFER_INDEX, 60);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_SOE_BUFFER_OLDEST, 60);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_SOE_BUFFER_DESC, 400);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_SOE_BUFFER_VALUE, 50);
        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_SOE_BUFFER_QUALITY, 150);
//        transmitTable->setColumnWidth(TABLE_TRANSMITINFO_SOE_BUFFER_TIME, 200);
        break;
    }
    default:
        break;
    }
}

void TransmitWidget::printTransmit()
{
    QPrinter printer;
    QPrintPreviewDialog preview(&printer, this);
    preview.setWindowFlags(Qt::Window);
    connect(&preview, SIGNAL(paintRequested(QPrinter *)), this, SLOT(onPrint(QPrinter *)));

    preview.exec();
}

bool TransmitWidget::setupPrinter()
{
    m_pPrinter->setFullPage(true);
    switch (QLocale::system().country())
    {
    case QLocale::AnyCountry:
    case QLocale::Canada:
    case QLocale::UnitedStates:
    case QLocale::UnitedStatesMinorOutlyingIslands:
        m_pPrinter->setPageSize(QPrinter::Letter);
        break;
    default:
        m_pPrinter->setPageSize(QPrinter::A4);
        break;
    }
    return true;
}

bool TransmitWidget::setupPage()
{

    return true;
}


void TransmitWidget::onPrint(QPrinter *pPrinter)
{
    pPrinter->setFullPage(true);

    QString html;
    int rows = 0;
    int columns = 0;
    ProxyModel *pModel = nullptr;
    switch(m_nTypeIndex)
    {
    case TRANSMIT_COS:
    {
        pModel = m_pCOSModel[m_nChnlIndex];
        rows = pModel->rowCount();
        columns = pModel->columnCount();
        html = "<table width=100% border=0 cellspacing=0><tr><td>"+TRANSMITINFO_INDEX+
                ",</td><td>"+TRANSMITINFO_INFOADDR+
                ",</td><td>"+TRANSMITINFO_IEDADDR+
                ",</td><td>"+TRANSMITINFO_DESC+
                ",</td><td>"+TRANSMITINFO_STATUSMODI+"</td></tr>";
        break;
    }
    case TRANSMIT_DO:
    {
        pModel = m_pDOModel[m_nChnlIndex];
        rows = pModel->rowCount();
        columns = pModel->columnCount();
        html = "<table width=100% border=0 cellspacing=0><tr><td>"+TRANSMITINFO_INDEX+
                ",</td><td>"+TRANSMITINFO_INFOADDR+
                ",</td><td>"+TRANSMITINFO_IEDADDR+
                ",</td><td>"+TRANSMITINFO_DESC+"</td></tr>";
        break;
    }
    case TRANSMIT_AI:
    {
        pModel = m_pAIModel[m_nChnlIndex];
        rows = pModel->rowCount();
        columns = pModel->columnCount();
        html = "<table width=100% border=0 cellspacing=0><tr><td>"+TRANSMITINFO_INDEX+
                ",</td><td>"+TRANSMITINFO_INFOADDR+
                ",</td><td>"+TRANSMITINFO_IEDADDR+
                ",</td><td>"+TRANSMITINFO_DESC+
                ",</td><td>"+TRANSMITINFO_THRESHOLD_TYPE+
                ",</td><td>"+TRANSMITINFO_THRESHOLD+
                ",</td><td>"+TRANSMITINFO_OFFSET+
                ",</td><td>"+TRANSMITINFO_MULTIFACTOR+"</td></tr>";
        break;
    }
    default:
        break;
    }

    for( int i = 0; i < rows; ++i )
    {
        html += "<tr>";
        for( int j = 0; j < columns; ++j )
        {
            html += "<td>" + pModel->data(pModel->index(i, j)).toString();
            if(j < columns-1)
                html += ",</td>";
            else
                html += "</td>";
        }
        html += "</tr>";
    }
    html += "</table>";

    QTextDocument textDocument;
    textDocument.setHtml(html);
    textDocument.print(pPrinter);
}

void TransmitWidget::onCallTriggered()
{
    emit callSignl();
}

void TransmitWidget::onExportExcelTriggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString masterName;
    transmitTree->getCurrentItemFullName(masterName);
    masterName.append("_").append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QString fileName = QFileDialog::getSaveFileName(this, TRANSMIT_EXPORT_EXCEL, masterName, tr("Microsoft Office 2007 (*.xlsx);;All Files (*)"), &selectedFilter, options);
    if (fileName.isEmpty())
    {
        return;
    }

    //建立Excel对象
    Document xlsx;

    int rows = 0;
    int columns = 0;
    ProxyModel *pModel = nullptr;
    switch(m_nTypeIndex)
    {
    case TRANSMIT_COS:
    {
        pModel = m_pCOSModel[m_nChnlIndex];
        rows = pModel->rowCount();
        columns = pModel->columnCount();
        QProgressDialog process1(this);
        process1.setLabelText(QStringLiteral("正在导出遥信..."));
        process1.setRange(0, rows*columns);
        process1.setModal(true);
        process1.setCancelButtonText(QStringLiteral("取消"));
        xlsx.addSheet(QStringLiteral("遥信"));
        xlsx.write(1, TABLE_TRANSMITINFO_COS_INDEX+1, TRANSMITINFO_INDEX);
        xlsx.write(1, TABLE_TRANSMITINFO_COS_INFOADDR+1, TRANSMITINFO_INFOADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_COS_IEDADDR+1, TRANSMITINFO_IEDADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_COS_DESC+1, TRANSMITINFO_DESC);
        xlsx.write(1, TABLE_TRANSMITINFO_COS_STATUSMODI+1, TRANSMITINFO_STATUSMODI);
        for( int i = 2; i <= rows; ++i )
        {
            for( int j = 1; j <= columns; ++j )
            {
                xlsx.write(i, j, pModel->data(pModel->index(i-2, j-1)));
            }
            process1.setValue(i*columns);
        }
        break;
    }
    case TRANSMIT_DO:
    {
        pModel = m_pDOModel[m_nChnlIndex];
        rows = pModel->rowCount();
        columns = pModel->columnCount();
        QProgressDialog process2(this);
        process2.setLabelText(QStringLiteral("正在导出遥控..."));
        process2.setRange(0, rows*columns);
        process2.setModal(true);
        process2.setCancelButtonText(QStringLiteral("取消"));
        xlsx.addSheet(QStringLiteral("遥控"));
        xlsx.write(1, TABLE_TRANSMITINFO_DO_INDEX+1, TRANSMITINFO_INDEX);
        xlsx.write(1, TABLE_TRANSMITINFO_DO_INFOADDR+1, TRANSMITINFO_INFOADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_DO_IEDADDR+1, TRANSMITINFO_IEDADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_DO_DESC+1, TRANSMITINFO_DESC);
        for( int i = 2; i <= rows; ++i )
        {
            for( int j = 1; j <= columns; ++j )
            {
                xlsx.write(i, j, pModel->data(pModel->index(i-2, j-1)));
            }
            process2.setValue(i*columns);
        }
        break;
    }
    case TRANSMIT_AI:
    {
        pModel = m_pAIModel[m_nChnlIndex];
        rows = pModel->rowCount();
        columns = pModel->columnCount();
        QProgressDialog process3(this);
        process3.setLabelText(QStringLiteral("正在导出遥测..."));
        process3.setRange(0, rows*columns);
        process3.setModal(true);
        process3.setCancelButtonText(QStringLiteral("取消"));
        xlsx.addSheet(QStringLiteral("遥测"));
        xlsx.write(1, TABLE_TRANSMITINFO_AI_INDEX+1, TRANSMITINFO_INDEX);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_INFOADDR+1, TRANSMITINFO_INFOADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_IEDADDR+1, TRANSMITINFO_IEDADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_DESC+1, TRANSMITINFO_DESC);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_THRESHOLD_TYPE+1, TRANSMITINFO_THRESHOLD_TYPE);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_THRESHOLD+1, TRANSMITINFO_THRESHOLD);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_OFFSET+1, TRANSMITINFO_OFFSET);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_MULTIFACTOR+1, TRANSMITINFO_MULTIFACTOR);
        for( int i = 2; i <= rows; ++i )
        {
            for( int j = 1; j <= columns; ++j )
            {
                xlsx.write(i, j, pModel->data(pModel->index(i-2, j-1)));
            }
            process3.setValue(i*columns);
        }
        break;
    }
    case TRANSMIT_CHNL_S://
    {
        //保存遥测转发表
        pModel = m_pAIModel[m_nChnlIndex];
        rows = pModel->rowCount();
        columns = pModel->columnCount();
        QProgressDialog processAi(this);
        processAi.setLabelText(QStringLiteral("正在导出遥测..."));
        processAi.setRange(0, rows*columns);
        processAi.setModal(true);
        processAi.setCancelButtonText(QStringLiteral("取消"));
        xlsx.addSheet(QStringLiteral("遥测"));
        xlsx.write(1, TABLE_TRANSMITINFO_AI_INDEX+1, TRANSMITINFO_INDEX);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_INFOADDR+1, TRANSMITINFO_INFOADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_IEDADDR+1, TRANSMITINFO_IEDADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_DESC+1, TRANSMITINFO_DESC);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_THRESHOLD_TYPE+1, TRANSMITINFO_THRESHOLD_TYPE);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_THRESHOLD+1, TRANSMITINFO_THRESHOLD);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_OFFSET+1, TRANSMITINFO_OFFSET);
        xlsx.write(1, TABLE_TRANSMITINFO_AI_MULTIFACTOR+1, TRANSMITINFO_MULTIFACTOR);
        for( int i = 2; i <= rows; ++i )
        {
            for( int j = 1; j <= columns; ++j )
            {
                 xlsx.write(i, j, pModel->data(pModel->index(i-2, j-1)));
            }
            processAi.setValue(i*columns);
        }

        //保存遥信转发表
        xlsx.addSheet(QStringLiteral("遥信"));
        pModel = m_pCOSModel[m_nChnlIndex];
        rows = pModel->rowCount();
        columns = pModel->columnCount();
        QProgressDialog processCos(this);
        processCos.setLabelText(QStringLiteral("正在导出遥信..."));
        processCos.setRange(0, rows*columns);
        processCos.setModal(true);
        processCos.setCancelButtonText(QStringLiteral("取消"));
        xlsx.write(1, TABLE_TRANSMITINFO_COS_INDEX+1, TRANSMITINFO_INDEX);
        xlsx.write(1, TABLE_TRANSMITINFO_COS_INFOADDR+1, TRANSMITINFO_INFOADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_COS_IEDADDR+1, TRANSMITINFO_IEDADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_COS_DESC+1, TRANSMITINFO_DESC);
        xlsx.write(1, TABLE_TRANSMITINFO_COS_STATUSMODI+1, TRANSMITINFO_STATUSMODI);
        for( int i = 2; i <= rows; ++i )
        {
            for( int j = 1; j <= columns; ++j )
            {
                xlsx.write(i, j, pModel->data(pModel->index(i-2, j-1)));
            }
            processCos.setValue(i*columns);
        }

        //保存遥控转发表
        xlsx.addSheet(QStringLiteral("遥控"));
        pModel = m_pDOModel[m_nChnlIndex];
        rows = pModel->rowCount();
        columns = pModel->columnCount();
        QProgressDialog processDo(this);
        processDo.setLabelText(QStringLiteral("正在导出遥控..."));
        processDo.setRange(0, rows*columns);
        processDo.setModal(true);
        processDo.setCancelButtonText(QStringLiteral("取消"));
        xlsx.write(1, TABLE_TRANSMITINFO_DO_INDEX+1, TRANSMITINFO_INDEX);
        xlsx.write(1, TABLE_TRANSMITINFO_DO_INFOADDR+1, TRANSMITINFO_INFOADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_DO_IEDADDR+1, TRANSMITINFO_IEDADDR);
        xlsx.write(1, TABLE_TRANSMITINFO_DO_DESC+1, TRANSMITINFO_DESC);
        for( int i = 2; i <= rows; ++i )
        {
            for( int j = 1; j <= columns; ++j )
            {
                xlsx.write(i, j, pModel->data(pModel->index(i-2, j-1)));
            }
            processDo.setValue(i*columns);
        }

        break;
    }
    default:
        break;
    }

    xlsx.saveAs(fileName);
    QMessageBox::information(this, QStringLiteral("OK"), QStringLiteral("保存成功！"));
}

void TransmitWidget::onExportCsvTriggered()
{
    QFileDialog::Options options;
    QString selectedFilter;
    QString masterName;
    transmitTree->getCurrentItemFullName(masterName);
    masterName.append("_").append(QDateTime::currentDateTime().toString("yyyyMMddhhmmss"));
    QString fileName = QFileDialog::getSaveFileName(this, TRANSMIT_EXPORT_CSV, masterName, tr("CSV Files (*.csv);;All Files (*)"), &selectedFilter, options);
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Truncate))
        {
            QMessageBox::warning(this, tr("Application"), tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
            return;
        }

        QTextStream out( &file );

        int rows = 0;
        int columns = 0;
        ProxyModel *pModel = nullptr;
        switch(m_nTypeIndex)
        {
        case TRANSMIT_COS:
        {
            pModel = m_pCOSModel[m_nChnlIndex];
            rows = pModel->rowCount();
            columns = pModel->columnCount();
            out << TRANSMITINFO_INDEX <<",";
            out << TRANSMITINFO_INFOADDR <<",";
            out << TRANSMITINFO_IEDADDR <<",";
            out << TRANSMITINFO_DESC <<",";
            out << TRANSMITINFO_STATUSMODI <<"\n";
            break;
        }
        case TRANSMIT_DO:
        {
            pModel = m_pDOModel[m_nChnlIndex];
            rows = pModel->rowCount();
            columns = pModel->columnCount();
            out << TRANSMITINFO_INDEX <<",";
            out << TRANSMITINFO_INFOADDR <<",";
            out << TRANSMITINFO_IEDADDR <<",";
            out << TRANSMITINFO_DESC <<"\n";
            break;
        }
        case TRANSMIT_AI:
        case TRANSMIT_CHNL_S:
        {
            pModel = m_pAIModel[m_nChnlIndex];
            rows = pModel->rowCount();
            columns = pModel->columnCount();
            out << TRANSMITINFO_INDEX <<",";
            out << TRANSMITINFO_INFOADDR <<",";
            out << TRANSMITINFO_IEDADDR <<",";
            out << TRANSMITINFO_DESC <<",";
            out << TRANSMITINFO_THRESHOLD_TYPE <<",";
            out << TRANSMITINFO_THRESHOLD <<",";
            out << TRANSMITINFO_OFFSET <<",";
            out << TRANSMITINFO_MULTIFACTOR <<"\n";
            break;
        }
        default:
            break;
        }

#ifndef QT_NO_CURSOR
        QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

        for( int r = 0; r < rows; ++r )
        {
            for( int c = 0; c < columns; ++c )
            {
                out << pModel->data(pModel->index(r, c)).toString();
                if(c < columns-1)
                    out << ",";
                else
                    out << "\n";
            }
        }

#ifndef QT_NO_CURSOR
        QApplication::restoreOverrideCursor();
#endif

        file.close();
        QMessageBox::information(this, QStringLiteral("OK"), QStringLiteral("保存成功！"));
    }

    return;

}

void TransmitWidget::onTreeCustomContextMenuRequested(QPoint pos)
{
    treePopMenu->addAction(callAction);

    treePopMenu->exec(QCursor::pos());
}

void TransmitWidget::onTableCustomContextMenuRequested(QPoint pos)
{
    tablePopMenu->addAction(printAction);
    tablePopMenu->addSeparator();
    tablePopMenu->addAction(excelAction);
    tablePopMenu->addAction(csvAction);

    tablePopMenu->exec(QCursor::pos());
}

void TransmitWidget::displayTransmitTable(const QByteArray &buffer, int dbIndex)
{
    char pText[128];
    int nRecordNum = (unsigned char) buffer.data()[24];
    int nChannelId = (unsigned char) buffer.data()[25];
    const char *pBuffer = buffer.data() + HEADNUMBER;

    switch(dbIndex)
    {
    case TRANSMIT_CHNL_A_RSP:
    {
        for (int i = 0; i < nRecordNum; i++)
        {
            memcpy(pText, pBuffer, 16);
            pBuffer+= 16;

//            if (!transmitTree->searchItems(QStringLiteral("转发通道(") + QString::fromUtf8(pText) + QStringLiteral(")")))
//            {
//                transmitTree->insertItems(TRANSINFO_TRANSMIT, i, 0, QStringLiteral("转发通道(") + QString::fromUtf8(pText) + QStringLiteral(")"));
//            }
        }
        transmitTree->expandAll();
        break;
    }
    case TRANSMIT_CHNL_S_RSP:
    case TRANSMIT_AI_RSP:
    case TRANSMIT_COS_RSP:
    case TRANSMIT_DO_RSP:
    {
        if(nChannelId != m_nChnlIndex)
        {
            qDebug() << nChannelId << QStringLiteral("错误");
            return;
        }

        for (int i = 0; i < nRecordNum; i++)
        {
            unsigned char pointType = *pBuffer++;

            unsigned short int nIndex = 0;
            memcpy(&nIndex, pBuffer, 2);
            pBuffer += 2;
            QString index = QString::number(nIndex, 10);

            unsigned int tmp = 0;
            memcpy(&tmp, pBuffer, 4);
            pBuffer += 4;
            QString infoaddr = QString::number(tmp, 10);

            tmp = 0;
            memcpy(&tmp, pBuffer, 4);
            pBuffer += 4;
            QString iedaddr = QString::number(tmp, 10);

            char pText[128];
            memset(pText, 0, sizeof(pText));
            unsigned short int nDescLen = *pBuffer++;
            memcpy(pText, pBuffer, nDescLen);
            pBuffer += nDescLen;
            QString desc = QString::fromUtf8(pText);

            if(pointType == TRANSMIT_AI_RSP)
            {
                unsigned char thresholdType = *pBuffer++;

                float fValue = 0.0;
                char dataValue[20];

                memcpy(&fValue, pBuffer, 4);
                pBuffer += 4;
                sprintf(dataValue, "%.4f", fValue);
                QString threshold = QString(dataValue);

                memcpy(&fValue, pBuffer, 4);
                pBuffer += 4;
                sprintf(dataValue, "%.4f", fValue);
                QString offset = QString(dataValue);

                memcpy(&fValue, pBuffer, 4);
                pBuffer += 4;
                sprintf(dataValue, "%.4f", fValue);
                QString multifactor = QString(dataValue);

                QAbstractItemModel *model = m_pAIModel[m_nChnlIndex]->sourceModel();
                int arow = model->rowCount();
                model->insertRow(arow);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_AI_INDEX), index);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_AI_INFOADDR), infoaddr);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_AI_IEDADDR), iedaddr);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_AI_DESC), desc);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_AI_THRESHOLD_TYPE), QString(QStringLiteral("绝对值")));
                model->setData(model->index(arow, TABLE_TRANSMITINFO_AI_THRESHOLD), threshold);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_AI_OFFSET), offset);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_AI_MULTIFACTOR), multifactor);
            }
            else if(pointType == TRANSMIT_COS_RSP)
            {
                unsigned int nVal = 0;
                memcpy(&nVal, pBuffer, 4);
                pBuffer += 4;
                QString pointMode = QString::number(nVal, 10);

                QAbstractItemModel *model = m_pCOSModel[m_nChnlIndex]->sourceModel();
                int arow = model->rowCount();
                model->insertRow(arow);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_COS_INDEX), index);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_COS_INFOADDR), infoaddr);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_COS_IEDADDR), iedaddr);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_COS_DESC), desc);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_COS_STATUSMODI), pointMode);
            }
            else if(pointType == TRANSMIT_DO_RSP)
            {
                QAbstractItemModel *model = m_pDOModel[m_nChnlIndex]->sourceModel();
                int arow = model->rowCount();
                model->insertRow(arow);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_DO_INDEX), index);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_DO_INFOADDR), infoaddr);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_DO_IEDADDR), iedaddr);
                model->setData(model->index(arow, TABLE_TRANSMITINFO_DO_DESC), desc);
            }
        }
        break;
    }
    case SOE_BUFFER_CHNL_RSP:
    {
        for (int i = 0; i < nRecordNum; i++)
        {
            memcpy(pText, pBuffer, 16);
            pBuffer+= 16;

//            if (!transmitTree->searchItems(QStringLiteral("SOE通道(") + QString::fromUtf8(pText) + QStringLiteral(")")))
//            {
//                transmitTree->insertItems(TRANSINFO_SOEBUFFER, i, 0, QStringLiteral("SOE通道(") + QString::fromUtf8(pText) + QStringLiteral(")"));
//                unsigned int iednum = *pBuffer++;
//                for(int j=0; j<iednum; j++)
//                {
//                    unsigned int iedAddr = *pBuffer++;
//                    transmitTree->insertItems(TRANSINFO_SOEBUFFER, i, j+1, QStringLiteral("装置") + QString::number(j, 10) + QStringLiteral("_") + QString::number(iedAddr, 10));
//                }
//            }
        }
        transmitTree->expandAll();
        break;
    }
    case SOE_BUFFER_DATA_RSP:
    {
        for (int i = 0; i < nRecordNum; i++)
        {
            unsigned char soeType = *pBuffer++;

            unsigned int nIndex = 0;
            memcpy(&nIndex, pBuffer, 4);
            pBuffer += 4;
            QString soeIndex = QString::number(nIndex, 10);

            nIndex = 0;
            memcpy(&nIndex, pBuffer, 4);
            pBuffer += 4;
            QString oldest = QString::number(nIndex, 10);

            //描述
            char pText[128];
            memset(pText, 0, sizeof(pText));
            unsigned short int nDescLen = *pBuffer++;
            memcpy(pText, pBuffer, nDescLen);
            pBuffer += nDescLen;
            QString soeDesc = QString::fromUtf8(pText);

            unsigned char value = *pBuffer++;
            unsigned char soeValue = value&0x03;
            unsigned char soeQuality = value&0xFC;

//            qDebug() << value << soeValue << soeQuality;
            QString soeQualityStr;
            if((soeQuality>>7)&0x01)
                soeQualityStr += QString("IV:1 ");
            else
                soeQualityStr += QString("IV:0 ");

            if((soeQuality>>6)&0x01)
                soeQualityStr += QString("NT:1 ");
            else
                soeQualityStr += QString("NT:0 ");

            if((soeQuality>>5)&0x01)
                soeQualityStr += QString("SB:1 ");
            else
                soeQualityStr += QString("SB:0 ");

            if((soeQuality>>4)&0x01)
                soeQualityStr += QString("BL:1 ");
            else
                soeQualityStr += QString("BL:0 ");


            UDD_TIME time;
            memcpy(&time, pBuffer, sizeof(UDD_TIME));
            pBuffer+= sizeof(UDD_TIME);
            QString soeTime = QString::number(time.year, 10) + QString("-") +
                    QString::number(time.month, 10) + QString("-") +
                    QString::number(time.dayOfMonth, 10) + QString(" ") +
                    QString::number(time.hour, 10) + QString(":") +
                    QString::number(time.minutes, 10) + QString(":") +
                    QString::number(time.mSecsAndSecs/1000, 10) + QString(" ") +
                    QString::number(time.mSecsAndSecs%1000, 10);


            //
            QAbstractItemModel *model = m_pSoeBufferModel[m_nChnlIndex][m_nIedIndex]->sourceModel();
            int arow = model->rowCount();
            model->insertRow(arow);
            model->setData(model->index(arow, TABLE_TRANSMITINFO_SOE_BUFFER_TYPE), soeType);
            model->setData(model->index(arow, TABLE_TRANSMITINFO_SOE_BUFFER_INDEX), soeIndex);
            model->setData(model->index(arow, TABLE_TRANSMITINFO_SOE_BUFFER_OLDEST), oldest);
            model->setData(model->index(arow, TABLE_TRANSMITINFO_SOE_BUFFER_DESC), soeDesc);
            model->setData(model->index(arow, TABLE_TRANSMITINFO_SOE_BUFFER_VALUE), soeValue);
            model->setData(model->index(arow, TABLE_TRANSMITINFO_SOE_BUFFER_QUALITY), soeQualityStr);
            model->setData(model->index(arow, TABLE_TRANSMITINFO_SOE_BUFFER_TIME), soeTime);
        }
        break;
    }
    case TRANSMIT_END_RSP:
        emit endSignl();
        break;
    default:
        break;
    }

}
