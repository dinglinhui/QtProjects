#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include "graphtree.h"
#include "glwidget.h"

class GraphWidget: public QWidget {
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

signals:

public slots:

public:
    GraphTree * getGraphTree();
    GLWidget * getGraphView();

private:
    GraphTree *graphTree;
    GLWidget *graphView;
};

#endif // GRAPHWIDGET_H
