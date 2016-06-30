#include <QtGui>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDomDocument>
#include <QDialogButtonBox>
#include "configdialog.h"
#include "pcdefs.h"

GeneralTab::GeneralTab(QWidget *parent) :
    QWidget(parent)
{
    QGroupBox *communicationGroup = new QGroupBox(COMMUNICATION_CONFIG);

    QLabel *listenPortLabel = new QLabel(COMMUNICATION_LISTENPORT);
    listenPortLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    m_pListenPortEdit = new QLineEdit();
    m_pListenPortEdit->setText(XML_ELEMENT_PORT_DEFAULT);

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(listenPortLabel, 0, 0, 1, 1);
    gridLayout->addWidget(m_pListenPortEdit, 0, 1, 1, 1);
    communicationGroup->setLayout(gridLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(communicationGroup);
    mainLayout->addStretch(1);
    this->setLayout(mainLayout);
}

QString GeneralTab::getListenPort()
{
    return m_pListenPortEdit->displayText();
}

void GeneralTab::setListenPort(const QString &port)
{
    m_pListenPortEdit->setText(port);
}

void GeneralTab::changeTransPage(int id)
{
    m_pTransWidget->setCurrentIndex(id);
}

TransPage::TransPage(QWidget *parent) :
    QWidget(parent)
{
    QLabel *tcpPortLabel = new QLabel(COMMUNICATION_TCPPORT);
    tcpPortLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    m_pTcpPortEdit = new QLineEdit();
    m_pTcpPortEdit->setText(tr("6010"));

    QGridLayout *serverLayout = new QGridLayout;
    serverLayout->addWidget(tcpPortLabel, 0, 0);
    serverLayout->addWidget(m_pTcpPortEdit, 0, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(serverLayout);
    setLayout(mainLayout);
}

QString TransPage::getTransPort()
{
    return m_pTcpPortEdit->displayText();
}

void TransPage::setTransPort(const QString& port)
{
    m_pTcpPortEdit->setText(port);
}

ReservePage::ReservePage(QWidget *parent) :
    QWidget(parent)
{
    QLabel *descLabel = new QLabel(QStringLiteral("正常使用情况下不需要启用转发表功能！"));
    descLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(descLabel);
    setLayout(mainLayout);
}

PermissionsTab::PermissionsTab(QWidget *parent) :
    QWidget(parent)
{

}

ApplicationsTab::ApplicationsTab(QWidget *parent) :
    QWidget(parent)
{

}

////////////////////////////////////////////////////////////////////////////////
// ConfigDialog
////////////////////////////////////////////////////////////////////////////////
ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    generalTab(new GeneralTab()),
    permissionsTab(new PermissionsTab()),
    applicationsTab(new ApplicationsTab()),
    parser(new XmlParser())
{
    QTabWidget *tabWidget = new QTabWidget(parent);
    tabWidget->addTab(generalTab, GENERAL_CONFIG);
    tabWidget->addTab(permissionsTab, SYSTEM_CONFIG);
    tabWidget->addTab(applicationsTab, APPLICATION_CONFIG);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(CONFIRM);
    buttonBox->button(QDialogButtonBox::Cancel)->setText(CANCEL);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);

    this->setLayout(mainLayout);
    this->setWindowTitle(PCSERVER_CONFIG);

    QString port = parser->getValue(XML_ELEMENT_LISTEN_PORT);
    generalTab->setListenPort(port);
}

ConfigDialog::~ConfigDialog()
{
    if(nullptr != parser)
        delete parser, parser = nullptr;
}

GeneralTab *ConfigDialog::getGeneralTab()
{
    return generalTab;
}

bool ConfigDialog::saveConfig(void *context, const QString &type)
{
    parser->writeXml(context, type);
}
