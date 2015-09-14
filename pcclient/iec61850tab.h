/*
 * iec61850tab.h
 *
 *  Created on: 2014/2/25
 *      Author: dinglinhui
 */

#ifndef IEC61850TAB_H_
#define IEC61850TAB_H_

#include "iec61850tree.h"
#include "borderlayout.h"
#include "pcmodel.h"
#include "pctab.h"

class IEC61850Tab: public PCTab
{
Q_OBJECT

public:
	IEC61850Tab(int nTabIndex, QWidget *parent = 0);
	//
	QAbstractItemModel *createModel(QObject *parent);
	PCModel *getModel();
	//
	void masterFilterChanged(const QString & master);

	IEC61850Tree *masterTree;

private:
	BorderLayout *layout;

	QTableView *tableView;
	PCModel *proxyModel;
};

#endif /* IEC61850TAB_H_ */
