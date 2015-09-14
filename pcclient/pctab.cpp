/*
 * pctab.cpp
 *
 *  Created on: 2014/2/25
 *      Author: dinglinhui
 */

#include "pcdefs.h"
#include "pctab.h"

PCTab::PCTab(int nTabIndex, QWidget *parent) :
		m_nTabIndex(nTabIndex)
{

}

PCTab::~PCTab()
{
}

int PCTab::getTabIndex()
{
	return m_nTabIndex;
}
