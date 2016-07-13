#include <QSplitter>

#include "communicationwidget.h"
#include "borderlayout.h"

CommunicationWidget::CommunicationWidget(QWidget *parent) :
    QWidget(parent),
    commTree(new CommunicationTree(this)),
    commTable(new CommunicationTable(this)) {
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(commTree);
    splitter->addWidget(commTable);
    splitter->setStretchFactor(0, 20);
    splitter->setStretchFactor(1, 80);

    BorderLayout *layout = new BorderLayout;
    layout->addWidget(splitter, BorderLayout::Center);
    this->setLayout(layout);
}

CommunicationWidget::~CommunicationWidget() {

}

CommunicationTree * CommunicationWidget::getCommunicationTree() {
    return commTree;
}

CommunicationTable * CommunicationWidget::getCommunicationTable() {
    return commTable;
}
