#include <QtGui>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QApplication>
#include "commpkttab.h"
#include "pcdefs.h"

CommPktTab::CommPktTab(QWidget *parent):
    QWidget(parent),
    m_bRolling(false),
    m_nSaveTimes(0)
{
    popMenu = new QMenu(this);
    analyzeAction = new QAction(QIcon(":/system/images/analyze.png"), COMMPKT_POPMENU_ANALYZE, this);
    connect(analyzeAction, SIGNAL(triggered()), this, SLOT(on_analyzeActionTriggered()));

    clearAction = new QAction(COMMPKT_POPMENU_CLEAR, this);
    connect(clearAction, SIGNAL(triggered()), this, SLOT(on_clearActionTriggered()));

    saveAction = new QAction(COMMPKT_POPMENU_SAVEPACKET, this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(on_saveActionTriggered()));

    //
    proxyModel = new PCModel(this);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setSourceModel(createModel(this));
    //
    tableView = new QTableView;
    tableView->setModel(proxyModel);
    //	tableView->setSortingEnabled(true);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
    tableView->setFocusPolicy(Qt::ClickFocus);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setAlternatingRowColors(true);
    tableView->horizontalHeader()->setStretchLastSection(true);
    //	tableView->verticalHeader()->hide();
    tableView->setAutoScroll(true);
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn); //水平滚动条按需显示
    //  tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
    //	tableView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //	tableView->sortByColumn(TABLE_COMMPKT_TIME, Qt::AscendingOrder);

    tableView->setColumnWidth(TABLE_COMMPKT_MASTER, 100);
    tableView->setColumnWidth(TABLE_COMMPKT_SEND_RECV, 50);
    tableView->setColumnWidth(TABLE_COMMPKT_TIME, 200);

    connect(tableView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(on_doubleClicked(const QModelIndex &)));
    connect(tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_customContextMenuRequested(QPoint)));

    commpktTree = new CommPktTree();
    commpktTree->setSelectionBehavior(QAbstractItemView::SelectItems);
    commpktTree->setSelectionMode(QAbstractItemView::SingleSelection);
    commpktTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //	commpktTree->header()->setResizeMode(QHeaderView::ResizeToContents);
    commpktTree->header()->hide();
    //	commpktTree->setFont(font);
    commpktTree->expandAll();

    //
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(commpktTree);
    splitter->addWidget(tableView);
    splitter->setStretchFactor(0, 20);
    splitter->setStretchFactor(1, 80);

    layout = new BorderLayout;
    layout->addWidget(splitter, BorderLayout::Center);
    setLayout(layout);
}

bool CommPktTab::getRolling()
{
    return m_bRolling;
}

void CommPktTab::setRolling(bool nRolling)
{
    m_bRolling = nRolling;
}

void CommPktTab::analyzeCommPkt(int rowIndex)
{
    QModelIndex modelIndex;
    QVariant modelVari;
    QString modelStr;
    QStringList rowList;

    //通过参数获取当前行数，再通过行数获取整行的数据
    for (int i = 0; i < TABLE_COMMPKT_MAX_NUM; i++)
    {
        modelIndex = proxyModel->index(rowIndex, i);
        modelVari = proxyModel->data(modelIndex);
        modelStr = modelVari.toString();
        rowList << modelStr;
    }

    emit analyzePacketSignal(rowList);
}

void CommPktTab::masterFilterChanged(const QString & master) {
    QRegExp regExp(master);
    proxyModel->setFilterRegExp(regExp);
}

void CommPktTab::on_customContextMenuRequested(QPoint pos) {
    popMenu->addAction(analyzeAction);
    popMenu->addSeparator();
    popMenu->addAction(clearAction);
    popMenu->addAction(saveAction);

    popMenu->exec(QCursor::pos());
}

void CommPktTab::on_doubleClicked(const QModelIndex &index) {
    analyzeCommPkt(index.row());
}

void CommPktTab::on_clearActionTriggered() {
    proxyModel->removeRows(0, proxyModel->rowCount());
}

void CommPktTab::on_saveActionTriggered() {
    QFileDialog::Options options;
    QString selectedFilter;
    QString masterName;
    commpktTree->getCurrentItemName(masterName);
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    COMMPKT_POPMENU_SAVEPACKET,
                                                    masterName,
                                                    tr("Text Files (*.txt);;All Files (*)"),
                                                    &selectedFilter,
                                                    options);

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Application"), tr("Cannot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
            return;
        }

        QTextStream out(&file);
#ifndef QT_NO_CURSOR
        QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
        for (int rowIndex = 0; rowIndex < proxyModel->rowCount(); rowIndex++) {
            out << proxyModel->data(proxyModel->index(rowIndex, TABLE_COMMPKT_MASTER)).toString() << "\t";
            out << proxyModel->data(proxyModel->index(rowIndex, TABLE_COMMPKT_SEND_RECV)).toString() << "\t";
            out << proxyModel->data(proxyModel->index(rowIndex, TABLE_COMMPKT_TIME)).toString() << "\n";
            out << proxyModel->data(proxyModel->index(rowIndex, TABLE_COMMPKT_PACKET)).toString() << "\n\n";
        }

#ifndef QT_NO_CURSOR
        QApplication::restoreOverrideCursor();
#endif

        QMessageBox::information(this, QStringLiteral("OK"), QStringLiteral("保存成功！"));
    }
}

void CommPktTab::on_analyzeActionTriggered() {
    QModelIndex index = tableView->currentIndex();
    if (index.row() != -1) {
        analyzeCommPkt(index.row());
    }
}

/*递归删除文件夹,即使里面有内容
 **
 **dir :文件夹的名字,绝对路径和相对路径均可
 **
 **返回值 :成功后返回true;否则返回false
 */
bool CommPktTab::removeDirWithContent(const QString &dirName) {
    static QVector<QString> dirNames;
    QDir dir;
    QFileInfoList filst;
    QFileInfoList::iterator curFi;

    //初始化
    dirNames.clear();
    if (dir.exists()) {
        dirNames << dirName;
    } else {
        return true;
    }

    //遍历各级文件夹，并将这些文件夹中的文件删除
    for (int i = 0; i < dirNames.size(); ++i) {
        dir.setPath(dirNames[i]);
        filst = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::Readable | QDir::Writable | QDir::Hidden | QDir::NoDotAndDotDot, QDir::Name);
        if (filst.size() > 0) {
            curFi = filst.begin();
            while (curFi != filst.end()) {
                //遇到文件夹,则添加至文件夹列表dirs尾部
                if (curFi->isDir()) {
                    dirNames.push_back(curFi->filePath());
                } else if (curFi->isFile()) {
                    //遇到文件,则删除之
                    if (!dir.remove(curFi->fileName())) {
                        return false;
                    }
                }
                curFi++;
            } //end of while
        }
    }

    //删除文件夹
    for (int i = dirNames.size() - 1; i >= 0; --i) {
        dir.setPath(dirNames[i]);
        if (!dir.rmdir(".")) {
            return false;
        }
    }

    return true;
}

void CommPktTab::addPacketInfo(QAbstractItemModel *model, const QStringList &list) {
    QString mkdir = PCCLIENT_HOME.append("/packet");
    if (m_nSaveTimes >= 30) { //当保存的文件大于30个的时候
        removeDirWithContent(mkdir);
        m_nSaveTimes = 0;
    }

    if (proxyModel->rowCount() >= 5000) {
        QDir dir;
        if (!dir.exists(mkdir)) {
            if (dir.mkpath(mkdir)) {
                qDebug() << "Created dir" << mkdir << "success!";
            }
        }

        QString timeStr = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        QString fileName = mkdir.append("/packet_").append(timeStr).append(".txt");
        qDebug() << mkdir;
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            qDebug() << "open file" << fileName << " error!";
        }

        QTextStream out(&file);
#ifndef QT_NO_CURSOR
        QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
        for (int rowIndex = 0; rowIndex < proxyModel->rowCount(); rowIndex++) {
            out << proxyModel->data(proxyModel->index(rowIndex, TABLE_COMMPKT_MASTER)).toString() << "\t";
            out << proxyModel->data(proxyModel->index(rowIndex, TABLE_COMMPKT_SEND_RECV)).toString() << "\t";
            out << proxyModel->data(proxyModel->index(rowIndex, TABLE_COMMPKT_TIME)).toString() << "\t";
            out << proxyModel->data(proxyModel->index(rowIndex, TABLE_COMMPKT_PACKET)).toString() << "\n\n";
        }

#ifndef QT_NO_CURSOR
        QApplication::restoreOverrideCursor();
#endif
        proxyModel->removeRows(0, proxyModel->rowCount());
        m_nSaveTimes++;
    }
    //
    int index = model->rowCount();
    model->insertRow(index);
    model->setData(model->index(index, TABLE_COMMPKT_MASTER), list.at(TABLE_COMMPKT_MASTER));
    model->setData(model->index(index, TABLE_COMMPKT_SEND_RECV), list.at(TABLE_COMMPKT_SEND_RECV));
    model->setData(model->index(index, TABLE_COMMPKT_TIME), list.at(TABLE_COMMPKT_TIME));
    model->setData(model->index(index, TABLE_COMMPKT_PACKET), list.at(TABLE_COMMPKT_PACKET));
    tableView->scrollToBottom();
    //
    //	emit analyzeMasterSignal(QString(list.at(TABLE_COMMPKT_MASTER)));
    if (!commpktTree->searchItems(QString(list.at(TABLE_COMMPKT_MASTER)))) {
        commpktTree->insertItems(QString(list.at(TABLE_COMMPKT_MASTER)));
    }
}

QAbstractItemModel *CommPktTab::createModel(QObject *parent) {
    QStandardItemModel *model = new QStandardItemModel(0, TABLE_COMMPKT_MAX_NUM, parent);

    model->setHeaderData(TABLE_COMMPKT_MASTER, Qt::Horizontal, COMMPKT_MASTER);
    model->setHeaderData(TABLE_COMMPKT_SEND_RECV, Qt::Horizontal, COMMPKT_SEND_RECV);
    model->setHeaderData(TABLE_COMMPKT_TIME, Qt::Horizontal, COMMPKT_TIME);
    model->setHeaderData(TABLE_COMMPKT_PACKET, Qt::Horizontal, COMMPKT_PACKET);

    return model;
}

void CommPktTab::displayReport(const QByteArray &buffer) {
    if (!m_bRolling) {
        return;
    }

    QByteArray buf(buffer);
    QString masterName;
    QString ipAddr;
    QString pktDirection;
    QString pktContent;

    char pMasterText[16] = { 0 };
    qstrncpy(pMasterText, buf.data() + 7, 16);
    int nPktDirection = (unsigned char) buf.data()[23]; //0-发送；1-接收
    int nRecordNum = (unsigned char) buf.data()[24]; //默认为1

    //上报报文默认为1
    if (nRecordNum != 1) {
        qDebug() << "packet num error!" << nRecordNum;
        return;
    }

    for (int i = 0; i < nRecordNum; i++) {
        //COMMPKT_MASTER
        masterName = QString(pMasterText);
        //COMMPKT_SEND_RECV
        if (nPktDirection == PACKET_RECV) {
            pktDirection = QString(COMMPKT_RECV);
        } else {
            pktDirection = QString(COMMPKT_SEND);
        }
        //COMMPKT_TIME
        QDateTime time = QDateTime::currentDateTime(); //获取系统现在的时间
        QString timeStr = time.toString("yyyy-MM-dd hh:mm:ss zzz"); //设置显示格式
        //COMMPKT_PACKET
        QByteArray pkt;
        pkt.insert(0, buf.data() + HEADNUMBER, buf.size() - HEADNUMBER);		//将报文插入QByteArray
        pkt = pkt.toHex();		//再将QByteArray里的ASCII数据转成16进制数据，长度扩大了一倍

        for (int i = 0; i < pkt.size(); i += 2) {
            const char cTmp1 = pkt.data()[i];
            const char cTmp2 = pkt.data()[i + 1];
            pktContent.append(QString("%1%2 ").arg(QString(cTmp1).toUpper()).arg(QString(cTmp2).toUpper()));
            //qDebug() << pktContent << QString(cTmp1) << QString(cTmp2);
        }
        //
        QStringList list;
        list << masterName << pktDirection << timeStr << pktContent;
        addPacketInfo(proxyModel->sourceModel(), list);
    }
}
