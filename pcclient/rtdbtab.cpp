#include <QtGui>
#include <QMenu>
#include <QSplitter>
#include <QHeaderView>
#include "rtdbeditdlg.h"
#include "rtdbtab.h"
#include "itemdelegate.h"
#include "pcdefs.h"

RtdbTab::RtdbTab(QWidget *parent) :
    QWidget(parent),
    m_dbIndex(0),
    m_lastEditIndex(-1)
{
    //
    popMenu = new QMenu(this);
    refreshAllAction = new QAction(QIcon(":/system/images/256/refresh.png"), RTDBINFO_POPMENU_REFRESHALL, this);
    connect(refreshAllAction, SIGNAL(triggered()), this, SLOT(on_refreshAllActionTriggered()));

    refreshSingleAction = new QAction(QIcon(":/system/images/256/down.png"), RTDBINFO_POPMENU_REFRESHSINGLE, this);
    connect(refreshSingleAction, SIGNAL(triggered()), this, SLOT(on_refreshSingleActionTriggered()));

    saveRtdbAction = new QAction(QIcon(":/system/images/256/diskette.png"), RTDBINFO_POPMENU_SAVERTDB, this);
    connect(saveRtdbAction, SIGNAL(triggered()), this, SLOT(on_saveRtdbActionTriggered()));

    proxyModel = new PCModel[RTDB_MAX_NUM];
    for (int i = 0; i < RTDB_MAX_NUM; i++)
    {
        proxyModel[i].setDynamicSortFilter(true);
        proxyModel[i].setSourceModel(createModel(this));
    }

    tableView = new QTableView;
    tableView->setModel(&proxyModel[m_dbIndex]);
    tableView->setFocusPolicy(Qt::ClickFocus);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setAlternatingRowColors(true);
    //	tableView->setStyleSheet("QTableView{background-color: rgb(250, 250, 115);"
    //				"alternate-background-color: rgb(141, 163, 215);}");
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->horizontalHeader()->setHighlightSections(false);
    //	tableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    tableView->verticalHeader()->hide();
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setAutoScroll(true);
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    tableView->setColumnHidden(TABLE_RTDBINFO_DATAVALUE_SRC, true);
    tableView->setColumnWidth(TABLE_RTDBINFO_SADDR, 50);
    tableView->setColumnWidth(TABLE_RTDBINFO_DESC, 400);

    ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate(this);
    ValueDelegate *valueDelegate = new ValueDelegate(this);
    tableView->setItemDelegateForColumn(TABLE_RTDBINFO_SADDR, readOnlyDelegate);
    tableView->setItemDelegateForColumn(TABLE_RTDBINFO_DESC, readOnlyDelegate);
    tableView->setItemDelegateForColumn(TABLE_RTDBINFO_DATATYPE, readOnlyDelegate);
    tableView->setItemDelegateForColumn(TABLE_RTDBINFO_DATATYPE, readOnlyDelegate);
    tableView->setItemDelegateForColumn(TABLE_RTDBINFO_DATAVALUE, valueDelegate);
    tableView->setItemDelegateForColumn(TABLE_RTDBINFO_EDITFLAG, readOnlyDelegate);

    connect(tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(on_clicked(const QModelIndex &)));
    connect(tableView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_doubleClicked(const QModelIndex &)));
    connect(tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_customContextMenuRequested(QPoint)));

    //
    rtdbTree = new RtdbTree();
    rtdbTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //	rtdbTree->header()->setResizeMode(QHeaderView::ResizeToContents);
    rtdbTree->header()->hide();
    //		rtdbTree->setFont(font);
    rtdbTree->expandAll();

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(rtdbTree);
    splitter->addWidget(tableView);
    splitter->setStretchFactor(0, 20);
    splitter->setStretchFactor(1, 80);

    layout = new BorderLayout;
    layout->addWidget(splitter, BorderLayout::Center);
    this->setLayout(layout);
}

void RtdbTab::setEditFlag()
{
    if (m_lastEditIndex != -1)
    {
        QModelIndex modelIndex;
        modelIndex = proxyModel[m_dbIndex].index(m_lastEditIndex, TABLE_RTDBINFO_DATAVALUE_SRC);
        QString dataValueSrc = proxyModel[m_dbIndex].data(modelIndex).toString();

        modelIndex = proxyModel[m_dbIndex].index(m_lastEditIndex, TABLE_RTDBINFO_DATAVALUE);
        QString dataValueDesc = proxyModel[m_dbIndex].data(modelIndex).toString();
        if (dataValueSrc != dataValueDesc)
        {
            emit enableSaveDataSignal();

            modelIndex = proxyModel[m_dbIndex].index(m_lastEditIndex, TABLE_RTDBINFO_EDITFLAG);
            proxyModel[m_dbIndex].setData(modelIndex, QVariant(EDITED_FLAG));

            modelIndex = proxyModel[m_dbIndex].index(m_lastEditIndex, TABLE_RTDBINFO_DATAVALUE_SRC);
            proxyModel[m_dbIndex].setData(modelIndex, QVariant(dataValueDesc));

            //将修改的行数据存入QStringList，并将QStringList存入m_editList
            QModelIndex modelIndex;
            QVariant modelVari;
            QString modelStr;
            QStringList rowList;

            //通过参数获取当前行数，再通过行数获取整行的数据
            for (int i = 0; i < TABLE_RTDBINFO_MAX_NUM; i++)
            {
                modelIndex = proxyModel[m_dbIndex].index(m_lastEditIndex, i);
                modelVari = proxyModel[m_dbIndex].data(modelIndex);
                modelStr = modelVari.toString();
                rowList << modelStr;
            }
            m_editMap.insert(m_lastEditIndex, rowList);
        }

        m_lastEditIndex = -1;
    }
}

void RtdbTab::clearEditFlag()
{
    QMutableMapIterator<int, QStringList> it(m_editMap);
    while (it.hasNext())
    {
        it.next();
        QModelIndex modelIndex = proxyModel[m_dbIndex].index(it.key(), TABLE_RTDBINFO_EDITFLAG);
        proxyModel[m_dbIndex].setData(modelIndex, QVariant(""));
    }
}

QMap<int, QStringList>& RtdbTab::getEditMap()
{
    return m_editMap;
}

void RtdbTab::clearEditMap()
{
    m_editMap.clear();
}

void RtdbTab::on_clicked(const QModelIndex & index)
{
    setEditFlag();

    int row = index.row(); //获取当前行号
    if (row != -1)
    {
        emit enableRefreshSingleSignal();
    }
}

void RtdbTab::on_doubleClicked(const QModelIndex & index)
{
    m_lastEditIndex = index.row();
}

void RtdbTab::on_customContextMenuRequested(QPoint pos)
{
    popMenu->addAction(refreshAllAction);
    popMenu->addAction(refreshSingleAction);
    popMenu->addAction(saveRtdbAction);
    //	popMenu->addSeparator();
    //	popMenu->addAction(testRtdbAction);

    popMenu->exec(QCursor::pos());
}

void RtdbTab::on_testRtdbActionTriggered()
{
    RtdbEditDlg *red = new RtdbEditDlg(this);
    if (red->exec() == QDialog::Accepted)
    {

    }
    else
    {
        red->close();
    }
}

void RtdbTab::on_refreshAllActionTriggered()
{
    emit refreshAllRtdbSignal();
}

void RtdbTab::on_refreshSingleActionTriggered()
{
    emit refreshSingleRtdbSignal();
}

void RtdbTab::on_saveRtdbActionTriggered()
{
    emit saveRtdbDataSignal(m_editMap);
    clearEditFlag();
    clearEditMap();
}

int RtdbTab::delRtdbData(QAbstractItemModel *model, int dbIndex, const int saddr)
{
    for (int i = 0; i < model->rowCount(); i++)
    {
        QModelIndex modelIndex;
        modelIndex = proxyModel[dbIndex].index(i, TABLE_RTDBINFO_SADDR);
        if (proxyModel[dbIndex].data(modelIndex).toInt() == saddr)
        {
            model->removeRow(modelIndex.row(), modelIndex.parent());
            return modelIndex.row();
        }
    }

    return -1;
}

void RtdbTab::addRtdbData(QAbstractItemModel *model, const QStringList &list)
{
    addRtdbData(model, model->rowCount(), list);
}

void RtdbTab::addRtdbData(QAbstractItemModel *model, int index, const QStringList &list)
{
    if (index != -1)
    {
        model->insertRow(index);
        model->setData(model->index(index, TABLE_RTDBINFO_SADDR), list.at(TABLE_RTDBINFO_SADDR));
        model->setData(model->index(index, TABLE_RTDBINFO_DESC), list.at(TABLE_RTDBINFO_DESC));
        model->setData(model->index(index, TABLE_RTDBINFO_DATATYPE), list.at(TABLE_RTDBINFO_DATATYPE));
        model->setData(model->index(index, TABLE_RTDBINFO_DATAVALUE), list.at(TABLE_RTDBINFO_DATAVALUE));
        model->setData(model->index(index, TABLE_RTDBINFO_DATAVALUE_SRC), list.at(TABLE_RTDBINFO_DATAVALUE_SRC));
    }
}

QAbstractItemModel *RtdbTab::createModel(QObject *parent)
{
    QStandardItemModel *model = new QStandardItemModel(0, TABLE_RTDBINFO_MAX_NUM, parent);

    model->setHeaderData(TABLE_RTDBINFO_SADDR, Qt::Horizontal, RTDBINFO_SADDR);
    model->setHeaderData(TABLE_RTDBINFO_DESC, Qt::Horizontal, RTDBINFO_DESC);
    model->setHeaderData(TABLE_RTDBINFO_DATATYPE, Qt::Horizontal,
                         RTDBINFO_DATATYPE);
    model->setHeaderData(TABLE_RTDBINFO_DATAVALUE, Qt::Horizontal,
                         RTDBINFO_DATAVALUE);
    model->setHeaderData(TABLE_RTDBINFO_DATAVALUE_SRC, Qt::Horizontal,
                         RTDBINFO_DATAVALUE);
    model->setHeaderData(TABLE_RTDBINFO_EDITFLAG, Qt::Horizontal,
                         RTDBINFO_EDITFLAG);

    return model;
}

void RtdbTab::changeModel(int index)
{
    if(index != -1)
    {
        m_dbIndex = index;
        tableView->setModel(&proxyModel[m_dbIndex]);
    }
}

void RtdbTab::clearModel(int index)
{
    if (proxyModel[index].rowCount() > 0)
    {
        proxyModel[index].removeRows(0, proxyModel[index].rowCount());
    }
}

bool RtdbTab::isModelEmpty()
{
    return proxyModel[m_dbIndex].rowCount() == 0 ? true : false;
}

int RtdbTab::getCurrentRow(QStringList &list)
{
    int row = tableView->currentIndex().row();
    if (row != -1)
    {
        QModelIndex modelIndex;
        QVariant modelVari;
        QString modelStr;

        //通过参数获取当前行数，再通过行数获取整行的数据
        for (int i = 0; i < TABLE_RTDBINFO_MAX_NUM; i++)
        {
            modelIndex = proxyModel[m_dbIndex].index(row, i);
            modelVari = proxyModel[m_dbIndex].data(modelIndex);
            modelStr = modelVari.toString();
            list << modelStr;
        }
    }
    return row;
}

void RtdbTab::displayRtdbTable(const QByteArray &buffer, int dbIndex)
{
    QByteArray buf(buffer);

    QString sAddr;
    QString desc;
    QString dataType;
    char pText[128];
    char dataValue[20];

    int tableCount = 0, IntTemp = 0;
    int nRecordNum = (unsigned char) buf.data()[24];
    double doubleTemp = 0.0;

    const char *pBuffer = buf.data() + HEADNUMBER;

    for (int i = 0; i < nRecordNum; i++)
    {
        memcpy(&tableCount, pBuffer, 4);
        sAddr = QString::number(tableCount, 10);
        memcpy(pText, pBuffer + 4, 128);
        desc = QString::fromUtf8(pText);
        if (pBuffer[132] == INTGER_DATA)
        {
            dataType = DATATYPE_INT;
            memcpy(&IntTemp, pBuffer + 133, 4);
            sprintf(dataValue, "%d", IntTemp);
            pBuffer += 137;
        }
        else if (pBuffer[132] == DOUBLE_DATA)
        {
            dataType = DATATYPE_FLOAT;
            memcpy(&doubleTemp, pBuffer + 133, 8);
            sprintf(dataValue, "%.4f", doubleTemp);
            pBuffer += 141;
        }

        QStringList list;
        list << sAddr << desc << dataType << QString(dataValue) << QString(dataValue);
        addRtdbData(proxyModel[dbIndex].sourceModel(), list);
    }
}

void RtdbTab::updateRtdbTable(const QByteArray &buffer, int dbIndex)
{
    QByteArray buf(buffer);

    QString sAddr;
    QString desc;
    QString dataType;
    char pText[128];
    char dataValue[20];

    int tableCount = 0, IntTemp = 0;
    int nRecordNum = (unsigned char) buf.data()[24];
    double doubleTemp = 0.0;
    const char *pBuffer = buf.data() + HEADNUMBER;

    if (nRecordNum != 1)
    {
        qDebug() << nRecordNum << "error";
        return;
    }

    for (int i = 0; i < nRecordNum; i++)
    {
        memcpy(&tableCount, pBuffer, 4);
        sAddr = QString::number(tableCount, 10);
        memcpy(pText, pBuffer + 4, 128);
        desc = QString::fromUtf8(pText);
        if (pBuffer[132] == INTGER_DATA)
        {
            dataType = DATATYPE_INT;
            memcpy(&IntTemp, pBuffer + 133, 4);
            sprintf(dataValue, "%d", IntTemp);
            pBuffer += 137;
        }
        else if (pBuffer[132] == DOUBLE_DATA)
        {
            dataType = DATATYPE_FLOAT;
            memcpy(&doubleTemp, pBuffer + 133, 8);
            sprintf(dataValue, "%.4f", doubleTemp);
            pBuffer += 141;
        }

        QStringList list;
        list << sAddr << desc << dataType << QString(dataValue) << QString(dataValue);

        int index = delRtdbData(proxyModel[dbIndex].sourceModel(), dbIndex, tableCount);
        addRtdbData(proxyModel[dbIndex].sourceModel(), index, list);
        /*proxyModel[dbIndex].sourceModel()->removeRow(tableCount);
         addRtdbData(proxyModel[dbIndex].sourceModel(), tableCount, list);*/
    }
}

