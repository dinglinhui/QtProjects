#include <QSplitter>

#include "graphwidget.h"
#include "borderlayout.h"

GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent),
    graphTree(new GraphTree(this)),
    graphView(new GLWidget()) {

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(graphTree);
    splitter->addWidget(graphView);
    splitter->setStretchFactor(0, 45);
    splitter->setStretchFactor(1, 55);

    BorderLayout *layout = new BorderLayout;
    layout->addWidget(splitter, BorderLayout::Center);
    this->setLayout(layout);
}

GraphWidget::~GraphWidget() {

}

GraphTree * GraphWidget::getGraphTree() {
    return graphTree;
}

GLWidget * GraphWidget::getGraphView() {
    return graphView;
}
