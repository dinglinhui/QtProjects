#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H

#include <QTreeView>
#include <QTableView>
#include <QTabWidget>
#include <QItemSelection>
#include "pcdefs.h"
#include "welcomewidget.h"
#include "mainwidget.h"
#include "graphwidget.h"
#include "examinationwidget.h"
#include "communicationwidget.h"

class TabWidget: public QTabWidget {
    Q_OBJECT

public:
    TabWidget(QWidget *parent = 0);
    ~TabWidget();

public:
    void addGraphTab();
    void addConnManageTab();
    void addExamManageTab();

public slots:
    void onSocketConnect(const int socketDescriptor, const QString & ip, const quint16 port);
    void onSocketDisConnect(const int socketDescriptor, const QString & ip, const quint16 port);

    void removeSubTab(int index);

private:
    WelcomeWidget *welcomWidget = nullptr;
    GraphWidget *graphWidget = nullptr;
    ExaminationWidget *examinationWidget = nullptr;
    CommunicationWidget *communicationWidget = nullptr;
};

#endif
