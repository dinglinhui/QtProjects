#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H

#include <QTreeView>
#include <QTableView>
#include <QTabWidget>
#include <QItemSelection>
#include "pcdefs.h"
#include "welcomewidget.h"
#include "transmitwidget.h"

class TabWidget: public QTabWidget
{
    Q_OBJECT

public:
    TabWidget(QWidget *parent = 0);
    ~TabWidget();


public slots:
    void onSocketConnect(const int socketDescriptor, const QString & ip, const quint16 port);
    void onSocketDisConnect(const int socketDescriptor, const QString & ip, const quint16 port);

    void removeSubTab(int index);

private:
//    WelcomeWidget *welcomWidget;
    TransmitWidget *transmitWidget = nullptr;
};

#endif
