#ifndef COMMCFGDLG_H
#define COMMCFGDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QTabWidget>
#include <QStackedWidget>
#include "xmlparser.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
QT_END_NAMESPACE

class TransPage: public QWidget {
public:
    TransPage(QWidget *parent = 0);

    QString getTransPort();
    void setTransPort(const QString& port);

private:
    QLineEdit *m_pTcpPortEdit;
};

class GeneralTab: public QWidget {
    Q_OBJECT

public:
    GeneralTab(QWidget *parent = 0);

    QString getListenPort();
    void setListenPort(const QString &port);

public slots:
    void changeTransPage(int id);

private:
    QLineEdit *m_pListenPortEdit;
    QStackedWidget *m_pTransWidget;
    TransPage *m_pTransPage;
};

class ReservePage: public QWidget {
public:
    ReservePage(QWidget *parent = 0);
};

class PermissionsTab: public QWidget {
    Q_OBJECT

public:
    PermissionsTab(QWidget *parent = 0);
};

class ApplicationsTab: public QWidget {
    Q_OBJECT

public:
    ApplicationsTab(QWidget *parent = 0);
};

class ConfigDialog: public QDialog {
    Q_OBJECT

public:
    ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

    GeneralTab *getGeneralTab();
    bool saveConfig(void *context = nullptr, const QString &type = XML_ELEMENT_SERVER);

private:
    GeneralTab *generalTab;
    PermissionsTab *permissionsTab;
    ApplicationsTab *applicationsTab;

    XmlParser *parser = nullptr;
};

#endif // COMMCFGDLG_H
