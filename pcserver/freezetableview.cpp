#include <QtGui>

#include "freezetableview.h"
#include <QHeaderView>
#include <QScrollBar>

//! [constructor]
FreezeTableView::FreezeTableView(QAbstractItemModel * model) {
	setModel(model);
	frozenTableView = new QTableView(this);

	init();

	//connect the headers and scrollbars of both tableviews together
	connect(horizontalHeader(), SIGNAL(sectionResized(int,int,int)), this, SLOT(updateSectionWidth(int,int,int)));
	connect(verticalHeader(), SIGNAL(sectionResized(int,int,int)), this, SLOT(updateSectionHeight(int,int,int)));

	connect(frozenTableView->verticalScrollBar(), SIGNAL(valueChanged(int)), verticalScrollBar(), SLOT(setValue(int)));
	connect(verticalScrollBar(), SIGNAL(valueChanged(int)), frozenTableView->verticalScrollBar(), SLOT(setValue(int)));

}
//! [constructor]

FreezeTableView::~FreezeTableView() {
	delete frozenTableView;
}

//! [init part1]
void FreezeTableView::init() {
	frozenTableView->setModel(model());
	frozenTableView->setFocusPolicy(Qt::NoFocus);
	frozenTableView->verticalHeader()->hide();
//	frozenTableView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);

	viewport()->stackUnder(frozenTableView);
//! [init part1]

//! [init part2]
	frozenTableView->setStyleSheet("QTableView { border: none;"
			"background-color: #8EDE21;"
			"selection-background-color: #999}"); //for demo purposes
	frozenTableView->setSelectionModel(selectionModel());
	for (int col = 1; col < model()->columnCount(); col++)
		frozenTableView->setColumnHidden(col, true);

	frozenTableView->setColumnWidth(0, columnWidth(0));

	frozenTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	frozenTableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	frozenTableView->show();

	updateFrozenTableGeometry();

	setHorizontalScrollMode(ScrollPerPixel);
	setVerticalScrollMode(ScrollPerPixel);
	frozenTableView->setVerticalScrollMode(ScrollPerPixel);
}
//! [init part2]

//! [sections]
void FreezeTableView::updateSectionWidth(int logicalIndex, int, int newSize) {
	if (logicalIndex == 0)
	{
		frozenTableView->setColumnWidth(0, newSize);
		updateFrozenTableGeometry();
	}
}

void FreezeTableView::updateSectionHeight(int logicalIndex, int, int newSize) {
	frozenTableView->setRowHeight(logicalIndex, newSize);
}
//! [sections]

//! [resize]
void FreezeTableView::resizeEvent(QResizeEvent * event) {
	QTableView::resizeEvent(event);
	updateFrozenTableGeometry();
}
//! [resize]

//! [navigate]
QModelIndex FreezeTableView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
	QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

	if (cursorAction == MoveLeft && current.column() > 0 && visualRect(current).topLeft().x() < frozenTableView->columnWidth(0))
	{
		const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x() - frozenTableView->columnWidth(0);
		horizontalScrollBar()->setValue(newValue);
	}
	return current;
}
//! [navigate]

void FreezeTableView::scrollTo(const QModelIndex & index, ScrollHint hint)
{
	if (index.column() > 0)
		QTableView::scrollTo(index, hint);
}

//! [geometry]
void FreezeTableView::updateFrozenTableGeometry()
{
	frozenTableView->setGeometry(verticalHeader()->width() + frameWidth(), frameWidth(), columnWidth(0), viewport()->height() + horizontalHeader()->height());
}
//! [geometry]

