#ifndef GRAPHTREE_H
#define GRAPHTREE_H

#include <QTreeView>
#include <QList>
#include <QMenu>
#include <QStandardItem>
#include <QMouseEvent>

class GraphTree: public QTreeView {
    Q_OBJECT
public:
    explicit GraphTree(QWidget *parent = 0);
    ~GraphTree();
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
    void clearItems();
    //
    QList<QStandardItem *> returnTheItems();
    QList<QStandardItem *> returnTheItems(const QString &text);
    QList<QStandardItem *> returnTheItems(const QString &text, Qt::MatchFlags flags);

    void mousePressEvent(QMouseEvent *event);

    QStandardItemModel *getModel();

public slots:
    void onTreeCustomContextMenuRequested(QPoint pos);

signals:
    void treeClicked(const QModelIndex &index);

private:
    QStandardItemModel *treeModel;
    QStandardItem *graph;
    QMenu *treePopMenu;
    QAction *callAction;
};

#endif // GRAPHTREE_H
