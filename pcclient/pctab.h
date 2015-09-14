/*
 * pctab.h
 *
 *  Created on: 2014年2月25日
 *      Author: dinglinhui
 */

#ifndef PCTAB_H_
#define PCTAB_H_

#include <QWidget>
#include <QTreeView>
#include <QTextEdit>
#include <QTableView>
#include <QTabWidget>
#include <QItemSelection>
#include <QStringList>
#include <QStandardItemModel>

class PCTab : public QWidget
{
    Q_OBJECT

public:
    PCTab(int nTabIndex, QWidget *parent = 0);
    virtual ~PCTab();

    int getTabIndex();

private:
    int m_nTabIndex;
};

#endif /* PCTAB_H_ */
