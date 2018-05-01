#ifndef NOFOCUSFRAMEDELEGATE_H
#define NOFOCUSFRAMEDELEGATE_H

#include <QStyledItemDelegate>

class NoFocusFrameDelegate : public QStyledItemDelegate
{
public:
    NoFocusFrameDelegate(QObject *parent);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // NOFOCUSFRAMEDELEGATE_H
