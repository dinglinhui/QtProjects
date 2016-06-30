#include <QHeaderView>
#include <QMouseEvent>
#include "examinationtree.h"

ExaminationTree::ExaminationTree(QWidget *parent) :
    QTreeView(parent),
    m_pParent(parent),
    treeModel(new QStandardItemModel(1, 1)),
    examManage(new QStandardItem(EXAM_LIST)),
    treePopMenu(new QMenu(this)),
    callAction(new QAction(QIcon(":/res/images/256/reload.png"), COMMUNICATION_CALL, this))
{
    examManage->setIcon(QIcon(":/res/images/256/document.png"));

    treeModel->setHeaderData(0, Qt::Horizontal, EXAM_LIST);
    treeModel->setItem(0, 0, examManage);

    this->setModel(treeModel);
    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->header()->hide();
    this->expandAll();
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onTreeCustomContextMenuRequested(QPoint)));
    connect(this, SIGNAL(treeClicked(const QModelIndex &)), m_pParent, SLOT(onTreeClicked(const QModelIndex &)));
}

ExaminationTree::~ExaminationTree()
{
    m_pParent = nullptr;
}

QStandardItemModel *ExaminationTree::getModel()
{
    return treeModel;
}

void ExaminationTree::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);

    if (event->buttons() == Qt::LeftButton)
    {
        emit treeClicked(currentIndex());
    }
}

void ExaminationTree::onTreeCustomContextMenuRequested(QPoint pos)
{
    treePopMenu->addAction(callAction);

    treePopMenu->exec(QCursor::pos());
}
