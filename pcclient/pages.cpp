#include <QtGui>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSettings>
#include "pages.h"

ConfigurationPage::ConfigurationPage(QWidget *parent) :
        QWidget(parent)
{
    /////////////////////////////////////////////////////////////////
    QGroupBox *configGroup = new QGroupBox(QStringLiteral("通道配置"));
    configGroup->setStyleSheet(QString("QGroupBox:title { color: blue; }"));

    QLabel *channelLabel = new QLabel(QStringLiteral("通道名称:"));
    QLineEdit *channelEdit = new QLineEdit;
    channelEdit->setText(QStringLiteral("通道_"));

    QLabel *chnlTypeLabel = new QLabel(QStringLiteral("通道类型:"));
    QRadioButton *netRButton = new QRadioButton(QStringLiteral("网络"));
    QRadioButton *comRButton = new QRadioButton(QStringLiteral("串口"));
    QButtonGroup *chnlTypeGrp = new QButtonGroup();
    chnlTypeGrp->addButton(netRButton, 0);
    chnlTypeGrp->addButton(comRButton, 1);
    netRButton->setChecked(true);
    connect(chnlTypeGrp, SIGNAL(buttonReleased(int)), this, SLOT(changeCommPage(int)));

    QHBoxLayout *rbLayout = new QHBoxLayout();
    rbLayout->addWidget(netRButton);
    rbLayout->addWidget(comRButton);

    QLabel *protocalLabel = new QLabel(QStringLiteral("规约类型:"));
    QComboBox *protocalCombo = new QComboBox;
    protocalCombo->addItem(QStringLiteral("南瑞继保103"));
    protocalCombo->addItem(QStringLiteral("南瑞科技103"));
    protocalCombo->addItem(QStringLiteral("IEC60870-5-101"));
    protocalCombo->addItem(QStringLiteral("IEC60870-5-103"));
    protocalCombo->addItem(QStringLiteral("IEC60870-5-104"));

    QGridLayout *serverLayout = new QGridLayout;
    serverLayout->addWidget(channelLabel, 0, 0);
    serverLayout->addWidget(channelEdit, 0, 1);
    serverLayout->addWidget(protocalLabel, 1, 0);
    serverLayout->addWidget(protocalCombo, 1, 1);
    serverLayout->addWidget(chnlTypeLabel, 2, 0);
    serverLayout->addLayout(rbLayout, 2, 1);

    configGroup->setLayout(serverLayout);

    /////////////////////////////////////////////////////////////////
    commcfgWidget = new QStackedWidget;
    commcfgWidget->addWidget(new NetPage);
    commcfgWidget->addWidget(new ComPage);

    QGroupBox *commGroup = new QGroupBox(QStringLiteral("通信配置"));
    commGroup->setStyleSheet(QString("QGroupBox:title { color: blue; }"));
    QHBoxLayout *commLayout = new QHBoxLayout();
    commLayout->addWidget(commcfgWidget, 0, Qt::AlignLeft);
    commGroup->setLayout(commLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
//	mainLayout->addStretch(1);
    mainLayout->addWidget(commGroup); //addWidget(commcfgWidget);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void ConfigurationPage::changeCommPage(int id)
{
    commcfgWidget->setCurrentIndex(id);
}

UpdatePage::UpdatePage(QWidget *parent) :
        QWidget(parent)
{
    ///////////////////////////////////////////////
    QGroupBox *updateGroup = new QGroupBox(QStringLiteral("终端参数"));
    updateGroup->setStyleSheet(QString("QGroupBox:title { color: blue; }"));
    QLabel *linkaddrLabel = new QLabel(QStringLiteral("链路地址:"));
    QLineEdit *linkaddrEdit = new QLineEdit();
    QLabel *commaddrLabel = new QLabel(QStringLiteral("公共地址:"));
    QLineEdit *commaddrEdit = new QLineEdit();
    QLabel *linkaddrlenLabel = new QLabel(QStringLiteral("链路地址长度:"));
    QComboBox *linkaddrlenCombo = new QComboBox;
    linkaddrlenCombo->addItem(QStringLiteral("1"));
    linkaddrlenCombo->addItem(QStringLiteral("2"));
    QLabel *commaddrlenLabel = new QLabel(QStringLiteral("公共地址长度:"));
    QComboBox *commaddrlenCombo = new QComboBox;
    commaddrlenCombo->addItem(QStringLiteral("1"));
    commaddrlenCombo->addItem(QStringLiteral("2"));
    QLabel *infoaddrlenLabel = new QLabel(QStringLiteral("信息地址长度:"));
    QComboBox *infoaddrlenCombo = new QComboBox;
    infoaddrlenCombo->addItem(tr("1"));
    infoaddrlenCombo->addItem(tr("2"));
    infoaddrlenCombo->addItem(tr("3"));
    QLabel *cotlenLabel = new QLabel(QStringLiteral("传送原因长度:"));
    QComboBox *cotlenCombo = new QComboBox;
    cotlenCombo->addItem(tr("1"));
    cotlenCombo->addItem(tr("2"));

    QGridLayout *serverLayout = new QGridLayout;
    serverLayout->addWidget(linkaddrLabel, 0, 0);
    serverLayout->addWidget(linkaddrEdit, 0, 1);
    serverLayout->addWidget(commaddrLabel, 1, 0);
    serverLayout->addWidget(commaddrEdit, 1, 1);
    serverLayout->addWidget(linkaddrlenLabel, 2, 0);
    serverLayout->addWidget(linkaddrlenCombo, 2, 1);
    serverLayout->addWidget(commaddrlenLabel, 3, 0);
    serverLayout->addWidget(commaddrlenCombo, 3, 1);
    serverLayout->addWidget(infoaddrlenLabel, 4, 0);
    serverLayout->addWidget(infoaddrlenCombo, 4, 1);
    serverLayout->addWidget(cotlenLabel, 5, 0);
    serverLayout->addWidget(cotlenCombo, 5, 1);
    updateGroup->setLayout(serverLayout);

    ///////////////////////////////////////////////
    QGroupBox *systemGroup = new QGroupBox(QStringLiteral("系统参数"));
    systemGroup->setStyleSheet(QString("QGroupBox:title { color: blue; }"));
    QLabel *localaddrLabel = new QLabel(QStringLiteral("本地地址:"));
    QLineEdit *localaddrEdit = new QLineEdit();
    localaddrEdit->setText(tr("1"));
    QLabel *sendtimeoutLabel = new QLabel(QStringLiteral("发送超时时间:"));
    QLineEdit *sendtimeouEdit = new QLineEdit();
    sendtimeouEdit->setText(tr("800"));
    QLabel *unitLabel1 = new QLabel(QStringLiteral("毫秒"));
    QLabel *recvtimeoutLabel = new QLabel(QStringLiteral("接收超时时间:"));
    QLineEdit *recvtimeoutEdit = new QLineEdit();
    recvtimeoutEdit->setText(tr("3"));
    QLabel *unitLabel2 = new QLabel(QStringLiteral("毫秒"));
    QLabel *buffsizeLabel = new QLabel(QStringLiteral("缓冲区大小:"));
    QLineEdit *buffsizeEdit = new QLineEdit();
    buffsizeEdit->setText(tr("1024"));
    QLabel *unitLabel4 = new QLabel(QStringLiteral("字节"));

    QGridLayout *systemLayout = new QGridLayout;
    systemLayout->addWidget(localaddrLabel, 0, 0);
    systemLayout->addWidget(localaddrEdit, 0, 1);
    systemLayout->addWidget(sendtimeoutLabel, 1, 0);
    systemLayout->addWidget(sendtimeouEdit, 1, 1);
    systemLayout->addWidget(unitLabel1, 1, 2);
    systemLayout->addWidget(recvtimeoutLabel, 2, 0);
    systemLayout->addWidget(recvtimeoutEdit, 2, 1);
    systemLayout->addWidget(unitLabel2, 2, 2);
    systemLayout->addWidget(buffsizeLabel, 3, 0);
    systemLayout->addWidget(buffsizeEdit, 3, 1);
    systemLayout->addWidget(unitLabel4, 3, 2);
    systemGroup->setLayout(systemLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(updateGroup);
//	mainLayout->addStretch(1);
    mainLayout->addWidget(systemGroup);
//	mainLayout->addSpacing(12);
    setLayout(mainLayout);
}

ComPage::ComPage(QWidget *parent) :
        QWidget(parent)
{
    //QGroupBox *configGroup = new QGroupBox(QStringLiteral("串口配置"));

    QLabel *comLabel = new QLabel(QStringLiteral("串口号:"));
    QComboBox *comCombo = new QComboBox;
    /*comCombo->addItem(tr("COM1"));
     comCombo->addItem(tr("COM2"));
     comCombo->addItem(tr("COM3"));
     comCombo->addItem(tr("COM4"));
     comCombo->addItem(tr("COM5"));*/

    QLabel *baudrLabel = new QLabel(QStringLiteral("波特率:"));
    QComboBox *baudrCombo = new QComboBox;
    baudrCombo->addItem(tr("110"), 0);
    baudrCombo->addItem(tr("300"), 1);
    baudrCombo->addItem(tr("600"), 2);
    baudrCombo->addItem(tr("1200"), 3);
    baudrCombo->addItem(tr("2400"), 4);
    baudrCombo->addItem(tr("4800"), 5);
    baudrCombo->addItem(tr("9600"), 6);
    baudrCombo->addItem(tr("14400"), 7);
    baudrCombo->addItem(tr("19200"), 8);
    baudrCombo->addItem(tr("38400"), 9);
    baudrCombo->addItem(tr("56000"), 10);
    baudrCombo->addItem(tr("64800"), 11);
    baudrCombo->addItem(tr("115200"), 12);
    baudrCombo->addItem(tr("128000"), 13);
    baudrCombo->addItem(tr("256000"), 14);
    baudrCombo->setCurrentIndex(6);
    QLabel *unitLabel1 = new QLabel(tr("bps"));

    QLabel *parityLabel = new QLabel(QStringLiteral("校验位:"));
    QComboBox *parityCombo = new QComboBox;
    parityCombo->addItem(tr("None"), 0);
    parityCombo->addItem(tr("Odd"), 1);
    parityCombo->addItem(tr("Even"), 2);
    parityCombo->addItem(tr("Mark"), 3);
    parityCombo->addItem(tr("Space"), 4);
    parityCombo->setCurrentIndex(2);

    QLabel *databLabel = new QLabel(QStringLiteral("数据位:"));
    QComboBox *databCombo = new QComboBox;
    databCombo->addItem(tr("7"), 0);
    databCombo->addItem(tr("8"), 1);
    databCombo->setCurrentIndex(1);

    QLabel *stopbLabel = new QLabel(QStringLiteral("停止位:"));
    QComboBox *stopbCombo = new QComboBox;
    stopbCombo->addItem(tr("1"), 0);
    stopbCombo->addItem(tr("1.5"), 1);
    stopbCombo->addItem(tr("2"), 2);
    stopbCombo->setCurrentIndex(0);

    QLabel *rtscLabel = new QLabel(QStringLiteral("RTS控制:"));
    QComboBox *rtscCombo = new QComboBox;
    rtscCombo->addItem(tr("Disable"));
    rtscCombo->addItem(tr("Enable"));

    QLabel *cmdtimeLabel = new QLabel(QStringLiteral("命令间隔:"));
    QLineEdit *cmdtimeEdit = new QLineEdit();
    cmdtimeEdit->setText(tr("100"));
    QLabel *unitLabel2 = new QLabel(QStringLiteral("毫秒"));

    QGridLayout *serverLayout = new QGridLayout;
    serverLayout->addWidget(comLabel, 0, 0);
    serverLayout->addWidget(comCombo, 0, 1);
    serverLayout->addWidget(baudrLabel, 1, 0);
    serverLayout->addWidget(baudrCombo, 1, 1);
    serverLayout->addWidget(unitLabel1, 1, 2);
    serverLayout->addWidget(parityLabel, 2, 0);
    serverLayout->addWidget(parityCombo, 2, 1);
    serverLayout->addWidget(databLabel, 3, 0);
    serverLayout->addWidget(databCombo, 3, 1);
    serverLayout->addWidget(stopbLabel, 4, 0);
    serverLayout->addWidget(stopbCombo, 4, 1);
    serverLayout->addWidget(rtscLabel, 5, 0);
    serverLayout->addWidget(rtscCombo, 5, 1);
    serverLayout->addWidget(cmdtimeLabel, 6, 0);
    serverLayout->addWidget(cmdtimeEdit, 6, 1);
    serverLayout->addWidget(unitLabel2, 6, 2);
//	serverLayout->setAlignment(Qt::AlignHCenter);
    //configGroup->setLayout(serverLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(serverLayout);	//addWidget(configGroup);
    setLayout(mainLayout);
}

NetPage::NetPage(QWidget *parent) :
        QWidget(parent)
{
    //QGroupBox *configGroup = new QGroupBox(QStringLiteral("网络配置"));

    QLabel *ipLabel = new QLabel(QStringLiteral("IP地址:"));
    QLineEdit *ipEdit = new QLineEdit(tr("127.0.0.1"));
    QLabel *tcpportLabel = new QLabel(QStringLiteral("TCP端口:"));
    QLineEdit *tcpportEdit = new QLineEdit(tr("6000"));
    QLabel *udpsportLabel = new QLabel(QStringLiteral("UDP源端口:"));
    QLineEdit *udpsportEdit = new QLineEdit(tr("6001"));
    QLabel *udpdportLabel = new QLabel(QStringLiteral("UDP目的端口:"));
    QLineEdit *udpdporttEdit = new QLineEdit(tr("6002"));
    QLabel *heartbeatLabel = new QLabel(QStringLiteral("心跳间隔:"));
    QLineEdit *heartbeatEdit = new QLineEdit();
    heartbeatEdit->setText(tr("10"));
    QLabel *unitLabel = new QLabel(QStringLiteral("秒"));

    QGridLayout *serverLayout = new QGridLayout;
    serverLayout->addWidget(ipLabel, 0, 0);
    serverLayout->addWidget(ipEdit, 0, 1);
    serverLayout->addWidget(tcpportLabel, 1, 0);
    serverLayout->addWidget(tcpportEdit, 1, 1);
    serverLayout->addWidget(udpsportLabel, 2, 0);
    serverLayout->addWidget(udpsportEdit, 2, 1);
    serverLayout->addWidget(udpdportLabel, 3, 0);
    serverLayout->addWidget(udpdporttEdit, 3, 1);
    serverLayout->addWidget(heartbeatLabel, 4, 0);
    serverLayout->addWidget(heartbeatEdit, 4, 1);
    serverLayout->addWidget(unitLabel, 4, 2);
//	serverLayout->setAlignment(Qt::AlignHCenter);
    //configGroup->setLayout(serverLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(serverLayout);	//addWidget(configGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
