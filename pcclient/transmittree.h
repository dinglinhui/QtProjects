#ifndef TRANSMITTREE_H
#define TRANSMITTREE_H

#include <QTreeView>
#include <QList>
#include <QStandardItem>
#include <QMouseEvent>

class TransmitTree: public QTreeView
{
    Q_OBJECT
public:
    explicit TransmitTree(QWidget *parent = 0);
    //
    QString getCurrentItemName();
    QString getCurrentItemName(QString &name);
    QString getCurrentItemFullName(QString &name);
    //
    void insertItems(int typeIndex, int chnlindex, int iedindex, const QString &text);
    void insertTransmitItems(const QString &text);
    void insertSoeBufferItems(int chnlindex, int iedindex, const QString &text);
    //
    bool searchItems(const QString &text);
    void clearItems(int typeIndex);
    //
    QList<QStandardItem *> returnTheItems();
    QList<QStandardItem *> returnTheItems(const QString &text);

    void mousePressEvent(QMouseEvent *event);

    QStandardItemModel *getModel();

signals:
    void treeClicked(const QModelIndex &index);

private:
    QStandardItemModel *model;
    QStandardItem *transmit;
    QStandardItem *soebuffer;
};


#endif // TRANSMITTREE_H
