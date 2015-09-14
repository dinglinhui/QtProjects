#include <QtGui>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QHeaderView>
#include "iec103tab.h"
#include "itemdelegate.h"
#include "pcdefs.h"

IEC103Tab::IEC103Tab(int nTabIndex, QWidget *parent) :
		PCTab(nTabIndex, parent)
{
	popMenu = new QMenu(this);
	channelAction = new QAction(QIcon(":/system/images/256/add.png"), IEC103_POPMENU_CREATE_CHANNEL, this);
	connect(channelAction, SIGNAL(triggered()), this, SLOT(on_channelActionTriggered()));

	chnlatrAction = new QAction(QIcon(":/system/images/256/certificate.png"), IEC103_POPMENU_CREATE_CHANNEL_ATTRIBUTE, this);
	connect(chnlatrAction, SIGNAL(triggered()), this, SLOT(on_channelAttrbuteActionTriggered()));

	connectAction = new QAction(QIcon(":/system/images/256/connect_vertical.png"), IEC103_POPMENU_CREATE_CONNECT, this);
	connect(connectAction, SIGNAL(triggered()), this, SLOT(on_connectActionTriggered()));

	disconnAction = new QAction(QIcon(":/system/images/256/disconnect_vertical.png"), IEC103_POPMENU_CREATE_DISCONNECT, this);
	connect(disconnAction, SIGNAL(triggered()), this, SLOT(on_disconnnectActionTriggered()));

	model = new QStandardItemModel();

	QFile file(":/grades.txt");
	QString line;
	QStringList list;
	if (file.open(QFile::ReadOnly))
	{
		line = file.readLine(200);
		list = line.simplified().split(",");
		model->setHorizontalHeaderLabels(list);

		int row = 0;
		QStandardItem *newItem = 0;
		while (file.canReadLine())
		{
			line = file.readLine(200);
			if (!line.startsWith("#") && line.contains(","))
			{
				list = line.simplified().split(",");
				for (int col = 0; col < list.length(); col++)
				{
					newItem = new QStandardItem(list.at(col));
					model->setItem(row, col, newItem);
				}
				row++;
			}
		}
	}
	file.close();

	tableView = new FreezeTableView(model);

	pktTxt = new QTextEdit;

	masterTree = new IEC103Tree();
	masterTree->setSelectionBehavior(QAbstractItemView::SelectItems);
	masterTree->setSelectionMode(QAbstractItemView::SingleSelection);
	masterTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
	masterTree->header()->hide();
	masterTree->expandAll();
	masterTree->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(masterTree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(on_customContextMenuRequested(QPoint)));

	QSplitter *vsplitter = new QSplitter(Qt::Vertical);
	vsplitter->setOpaqueResize(true);
	vsplitter->addWidget(tableView);
	vsplitter->addWidget(pktTxt);
	vsplitter->setStretchFactor(0, 70);
	vsplitter->setStretchFactor(1, 30);
	/*QSplitterHandle *splitterHandle = vsplitter->handle(1);
	 if (splitterHandle)
	 {
	 splitterHandle->setDisabled(true);
	 }*/

	QSplitter *hsplitter = new QSplitter(Qt::Horizontal);
	hsplitter->setOpaqueResize(true);
	hsplitter->addWidget(masterTree);
	hsplitter->addWidget(vsplitter);
	hsplitter->setStretchFactor(0, 20);
	hsplitter->setStretchFactor(1, 80);

	mainLayout = new BorderLayout;
	mainLayout->addWidget(hsplitter, BorderLayout::Center);

	this->setLayout(mainLayout);
}

IEC103Tab::~IEC103Tab()
{

}

QAbstractItemModel *IEC103Tab::createModel(QObject *parent)
{
	QStandardItemModel *model = new QStandardItemModel(0, TABLE_RTDBINFO_MAX_NUM, parent);

	model->setHeaderData(TABLE_RTDBINFO_SADDR, Qt::Horizontal, RTDBINFO_SADDR);
	model->setHeaderData(TABLE_RTDBINFO_DESC, Qt::Horizontal, RTDBINFO_DESC);
	model->setHeaderData(TABLE_RTDBINFO_DATATYPE, Qt::Horizontal, RTDBINFO_DATATYPE);
	model->setHeaderData(TABLE_RTDBINFO_DATAVALUE, Qt::Horizontal, RTDBINFO_DATAVALUE);
	model->setHeaderData(TABLE_RTDBINFO_DATAVALUE_SRC, Qt::Horizontal, RTDBINFO_DATAVALUE);
	model->setHeaderData(TABLE_RTDBINFO_EDITFLAG, Qt::Horizontal, RTDBINFO_EDITFLAG);

	return model;
}

void IEC103Tab::on_channelActionTriggered()
{
	QModelIndex index = masterTree->currentIndex();
	if (index.parent().row() == -1)
	{
	}
	else
	{
	}

	dialog = new ConfigDialog(QIcon(":/system/images/256/add.png"), IEC103_POPMENU_CREATE_CHANNEL);
	if (dialog->exec() == QDialog::Accepted)
	{

	}
	else
	{
		dialog->close();
	}
}

void IEC103Tab::on_channelAttrbuteActionTriggered()
{
	dialog = new ConfigDialog(QIcon(":/system/images/256/certificate.png"), IEC103_POPMENU_CREATE_CHANNEL_ATTRIBUTE);
	if (dialog->exec() == QDialog::Accepted)
	{

	}
	else
	{
		dialog->close();
	}
}

void IEC103Tab::on_connectActionTriggered()
{

}

void IEC103Tab::on_disconnnectActionTriggered()
{

}

void IEC103Tab::on_customContextMenuRequested(QPoint pos)
{
	popMenu->addAction(channelAction);
	popMenu->addSeparator();
	popMenu->addAction(chnlatrAction);
	chnlatrAction->setVisible(false);
	popMenu->addAction(connectAction);
	connectAction->setVisible(false);
	popMenu->addAction(disconnAction);
	disconnAction->setVisible(false);

	popMenu->exec(QCursor::pos());
}

