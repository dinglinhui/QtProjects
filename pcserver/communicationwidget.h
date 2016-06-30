#ifndef COMMUNICATIONWIDGET_H
#define COMMUNICATIONWIDGET_H

#include <QWidget>
#include "communicationtable.h"
#include "communicationtree.h"

class CommunicationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CommunicationWidget(QWidget *parent = 0);
    ~CommunicationWidget();

signals:

public slots:

public:
    CommunicationTree * getCommunicationTree();
    CommunicationTable * getCommunicationTable();

private:
    CommunicationTree *commTree;
    CommunicationTable *commTable;
};

#endif // COMMUNICATIONWIDGET_H
