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
    void insertItems(const QString &text, int linkIndex);
    void insertItems(const int socketDescriptor, const QString & ip, const quint16 port, int linkIndex);
    void insertTransmitItems(const QString &text, int linkIndex);
    //
    void removeItems(const QString &text);
    void removeTransmitItems(const QString &text, int linkIndex);
    //
    void changeItems(const QString &text, int linkIndex);
    //
    bool searchItems(const QString &text);
    bool searchItems(const QString &text, Qt::MatchFlags flags);
    void clearItems(int typeIndex);
    //
    QList<QStandardItem *> returnTheItems();
    QList<QStandardItem *> returnTheItems(const QString &text);
    QList<QStandardItem *> returnTheItems(const QString &text, Qt::MatchFlags flags);

    void mousePressEvent(QMouseEvent *event);

    QStandardItemModel *getModel();

signals:
    void treeClicked(const QModelIndex &index);

private:
    QStandardItemModel *treeModel;
//    QStandardItem *communicate;
    QStandardItem *transmit;
    QStandardItem *soebuffer;
};


#endif // TRANSMITTREE_H
