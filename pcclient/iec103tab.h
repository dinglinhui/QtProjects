#ifndef IEC103TAB_H_
#define IEC103TAB_H_

#include "pctab.h"
#include "borderlayout.h"
#include "iec103tree.h"
#include "freezetableview.h"
#include "configdialog.h"

class IEC103Tab: public PCTab
{
    Q_OBJECT
public:
	IEC103Tab(int nTabIndex, QWidget *parent = 0);
	virtual ~IEC103Tab();

	QAbstractItemModel *createModel(QObject *parent);
	IEC103Tree *masterTree;

private slots:
	void on_channelActionTriggered();
	void on_channelAttrbuteActionTriggered();
	void on_connectActionTriggered();
	void on_disconnnectActionTriggered();
	void on_customContextMenuRequested(QPoint pos);

private:
	BorderLayout *mainLayout;
	QStandardItemModel *model;
	FreezeTableView *tableView;
	QTextEdit *pktTxt;
	//
	QMenu *popMenu;
	QAction *channelAction;
	QAction *chnlatrAction;
	QAction *connectAction;
	QAction *disconnAction;
	//
	ConfigDialog *dialog;
};

#endif
