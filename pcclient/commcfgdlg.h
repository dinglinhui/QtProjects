#ifndef COMMCFGDLG_H
#define COMMCFGDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTabWidget>
#include <QStackedWidget>
#include "xmlparser.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
QT_END_NAMESPACE

class TransPage: public QWidget
{
public:
    TransPage(QWidget *parent = 0);

    QString getTransPort();
    void setTransPort(const QString& port);

private:
    QLineEdit *m_pTcpPortEdit;
};

class GeneralTab: public QWidget
{
    Q_OBJECT

public:
    GeneralTab(const QString &fileName, QWidget *parent = 0);

    QString getIP();
    QString getSrcPort();
    QString getDestPort();
    QString getTransPort();
    bool isTransEnable();

public slots:
    void changeTransPage(int id);

private:
    QLineEdit *m_pIpEdit;
    QLineEdit *m_pSrcPortEdit;
    QLineEdit *m_pDestPortEdit;
    QRadioButton *m_pYesRButton;
    QRadioButton *m_pNoRButton;
    QButtonGroup *m_pAskGrp;
    QStackedWidget *m_pTransWidget;
    TransPage *m_pTransPage;
};

class ReservePage: public QWidget
{
public:
    ReservePage(QWidget *parent = 0);
};

class PermissionsTab: public QWidget
{
    Q_OBJECT

public:
    PermissionsTab(const QString &fileName, QWidget *parent = 0);
};

class ApplicationsTab: public QWidget
{
    Q_OBJECT

public:
    ApplicationsTab(const QString &fileName, QWidget *parent = 0);
};

class CommCfgDlg: public QDialog
{
    Q_OBJECT

public:
    CommCfgDlg(const QString &fileName, QWidget *parent = 0);
    GeneralTab *getGeneralTab();

private:
    GeneralTab *m_pGeneralTab;
    PermissionsTab *m_pPermissionsTab;
    ApplicationsTab *m_pApplicationsTab;

    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
};

#endif // COMMCFGDLG_H
