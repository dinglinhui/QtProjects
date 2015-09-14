#include <QtGui>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QDomDocument>
#include <QDialogButtonBox>
#include "commcfgdlg.h"
#include "uddthread.h"
#include "pcdefs.h"

CommCfgDlg::CommCfgDlg(const QString &fileName, QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(parent);
    m_pGeneralTab = new GeneralTab(fileName);
//    m_pPermissionsTab = new PermissionsTab(fileName);
//    m_pApplicationsTab = new ApplicationsTab(fileName);
    tabWidget->addTab(m_pGeneralTab, GENERAL_CONFIG);
//    tabWidget->addTab(m_pPermissionsTab, OTHER_CONFIG);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
//    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    this->setLayout(mainLayout);
    this->setWindowTitle(COMMUNICATION_CONFIG);
}

GeneralTab *CommCfgDlg::getGeneralTab()
{
    return m_pGeneralTab;
}

GeneralTab::GeneralTab(const QString &fileName, QWidget *parent) :
    QWidget(parent)
{
    QGroupBox *communicationGroup = new QGroupBox(COMMUNICATION_CONFIG);

    QLabel *ipLabel = new QLabel(COMMUNICATION_IP);
    ipLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    m_pIpEdit = new QLineEdit();
    m_pIpEdit->setText(tr("127.0.0.1"));

    QLabel *srcPortLabel = new QLabel(COMMUNICATION_SRCPORT);
    srcPortLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    m_pSrcPortEdit = new QLineEdit();
    m_pSrcPortEdit->setText(tr("6009"));

    QLabel *destPortLabel = new QLabel(COMMUNICATION_DESTPORT);
    destPortLabel->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);
    m_pDestPortEdit = new QLineEdit();
    m_pDestPortEdit->setText(tr("6008"));

    QLabel *askLabel = new QLabel(QStringLiteral("转发表功能："));
    m_pYesRButton = new QRadioButton(QStringLiteral("启用"));
    m_pNoRButton = new QRadioButton(QStringLiteral("禁用"));
    m_pAskGrp = new QButtonGroup();
    m_pAskGrp->addButton(m_pYesRButton, 0);
    m_pAskGrp->addButton(m_pNoRButton, 1);
    m_pNoRButton->setChecked(true);
    connect(m_pAskGrp, SIGNAL(buttonReleased(int)), this, SLOT(changeTransPage(int)));
    QHBoxLayout *rbLayout = new QHBoxLayout();
    rbLayout->addWidget(m_pYesRButton);
    rbLayout->addWidget(m_pNoRButton);
    /////////////////////////////////////////////////////////////////
    m_pTransWidget = new QStackedWidget;
    m_pTransPage = new TransPage;
    m_pTransWidget->addWidget(m_pTransPage);
    m_pTransWidget->addWidget(new ReservePage);
    m_pTransWidget->setCurrentIndex(1);

    QGridLayout *gridLayout = new QGridLayout();
    //gridLayout->setSpacing(6);
    //gridLayout->setContentsMargins(40, 10, 40, 10);
    //gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

    gridLayout->addWidget(ipLabel, 0, 0, 1, 1);
    gridLayout->addWidget(m_pIpEdit, 0, 1, 1, 1);
    gridLayout->addWidget(srcPortLabel, 1, 0, 1, 1);
    gridLayout->addWidget(m_pSrcPortEdit, 1, 1, 1, 1);
    gridLayout->addWidget(destPortLabel, 2, 0, 1, 1);
    gridLayout->addWidget(m_pDestPortEdit, 2, 1, 1, 1);
    gridLayout->addWidget(askLabel, 3, 0, 1, 1);
    gridLayout->addLayout(rbLayout, 3, 1, 1, 1);
    gridLayout->addWidget(m_pTransWidget, 4, 0, 1, 2);
    communicationGroup->setLayout(gridLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(communicationGroup);
    mainLayout->addStretch(1);
    this->setLayout(mainLayout);

    SERVER_INFO Server;
    XmlParser parser;
    if (parser.readXml(fileName, XML_ELEMENT_SERVERINFO, &Server))
    {
        //qDebug() << fileName;
        m_pIpEdit->setText(Server.ip);
        m_pSrcPortEdit->setText(Server.srcPort);
        m_pDestPortEdit->setText(Server.destPort);
        m_pTransPage->setTransPort(Server.transPort);
        if(Server.transEnable.toInt())
        {
            m_pYesRButton->setChecked(true);
            m_pTransWidget->setCurrentIndex(0);
        }
    }
}

QString GeneralTab::getIP()
{
    return m_pIpEdit->displayText();
}

QString GeneralTab::getSrcPort()
{
    return m_pSrcPortEdit->displayText();
}

QString GeneralTab::getDestPort()
{
    return m_pDestPortEdit->displayText();
}

QString GeneralTab::getTransPort()
{
    return m_pTransPage->getTransPort();
}

bool GeneralTab::isTransEnable()
{
    return m_pYesRButton->isChecked();
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

PermissionsTab::PermissionsTab(const QString &fileName, QWidget *parent) :
    QWidget(parent)
{
    /*QGroupBox *permissionsGroup = new QGroupBox(tr("Permissions"));

     QCheckBox *readable = new QCheckBox(tr("Readable"));
     if (fileInfo.isReadable())
     readable->setChecked(true);

     QCheckBox *writable = new QCheckBox(tr("Writable"));
     if (fileInfo.isWritable())
     writable->setChecked(true);

     QCheckBox *executable = new QCheckBox(tr("Executable"));
     if (fileInfo.isExecutable())
     executable->setChecked(true);

     QGroupBox *ownerGroup = new QGroupBox(tr("Ownership"));

     QLabel *ownerLabel = new QLabel(tr("Owner"));
     QLabel *ownerValueLabel = new QLabel(fileInfo.owner());
     ownerValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

     QLabel *groupLabel = new QLabel(tr("Group"));
     QLabel *groupValueLabel = new QLabel(fileInfo.group());
     groupValueLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

     QVBoxLayout *permissionsLayout = new QVBoxLayout;
     permissionsLayout->addWidget(readable);
     permissionsLayout->addWidget(writable);
     permissionsLayout->addWidget(executable);
     permissionsGroup->setLayout(permissionsLayout);

     QVBoxLayout *ownerLayout = new QVBoxLayout;
     ownerLayout->addWidget(ownerLabel);
     ownerLayout->addWidget(ownerValueLabel);
     ownerLayout->addWidget(groupLabel);
     ownerLayout->addWidget(groupValueLabel);
     ownerGroup->setLayout(ownerLayout);

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(permissionsGroup);
     mainLayout->addWidget(ownerGroup);
     mainLayout->addStretch(1);
     setLayout(mainLayout);*/
}

ApplicationsTab::ApplicationsTab(const QString &fileName, QWidget *parent) :
    QWidget(parent)
{
    /*QLabel *topLabel = new QLabel(tr("Open with:"));

     QListWidget *applicationsListBox = new QListWidget;
     QStringList applications;

     for (int i = 1; i <= 30; ++i)
     applications.append(tr("Application %1").arg(i));
     applicationsListBox->insertItems(0, applications);

     QCheckBox *alwaysCheckBox;

     if (fileInfo.suffix().isEmpty())
     alwaysCheckBox = new QCheckBox(tr("Always use this application to "
     "open this type of file"));
     else
     alwaysCheckBox = new QCheckBox(tr("Always use this application to "
     "open files with the extension '%1'").arg(fileInfo.suffix()));

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(topLabel);
     layout->addWidget(applicationsListBox);
     layout->addWidget(alwaysCheckBox);
     setLayout(layout);*/
}

