#ifndef FREEZETABLEVIEW_H
#define FREEZETABLEVIEW_H

#include <QTableView>

class FreezeTableView: public QTableView
{
Q_OBJECT

public:
	FreezeTableView(QAbstractItemModel * model);
	~FreezeTableView();

protected:
	virtual void resizeEvent(QResizeEvent *event);
	virtual QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
	void scrollTo(const QModelIndex & index, ScrollHint hint = EnsureVisible);

private:
	QTableView *frozenTableView;
	void init();
	void updateFrozenTableGeometry();

private slots:
	void updateSectionWidth(int logicalIndex, int, int newSize);
	void updateSectionHeight(int logicalIndex, int, int newSize);

};
#endif
