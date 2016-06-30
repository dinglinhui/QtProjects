#include "networkinformation.h"

#include <QtGui>
#include <QHostInfo>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QNetworkInterface>

NetworkInformation::NetworkInformation(QWidget *parent)
    : QDialog(parent)
{
    nameLabel = new QLabel(tr("Name:"));
    nameEdit = new QLineEdit;
    nameLabel->setBuddy(nameEdit);
    nameEdit->setReadOnly(true);
    QString name = QHostInfo::localHostName();
    nameEdit->setText(name);

    ipLabel = new QLabel(tr("Ip:"));
    ipEdit = new QLineEdit;
    ipLabel->setBuddy(ipEdit);
    ipEdit->setReadOnly(true);
    QHostInfo hostInfo = QHostInfo::fromName(name);
    QList<QHostAddress> listAddress = hostInfo.addresses();
    if(!listAddress.empty())
        ipEdit->setText(listAddress.first().toString());

    detailButton = new QPushButton(tr("Detail"));
    connect(detailButton, SIGNAL(clicked()),
            this, SLOT(slotDetail()));

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(nameLabel);
    layout1->addWidget(nameEdit);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(ipLabel);
    layout2->addWidget(ipEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    mainLayout->addWidget(detailButton);
    setLayout(mainLayout);

    setWindowTitle(tr("Local Host Information"));
}

//private slots
void NetworkInformation::slotDetail()
{
    QString detail = "";
    QList<QNetworkInterface> listNetwork = QNetworkInterface::allInterfaces();
    for(int i = 0; i < listNetwork.count(); i++) {
        detail += "name: " + listNetwork.at(i).name() + "\n";
        detail += "hardware address: " + listNetwork.at(i).hardwareAddress() + "\n";
        QList<QNetworkAddressEntry> listAddress = listNetwork.at(i).addressEntries();
        for(int j = 0; j < listAddress.count(); j++) {
            detail += "ip: " + listAddress.at(j).ip().toString() + "\n";
            detail += "netmask: " + listAddress.at(j).netmask().toString() + "\n";
            detail += "broadcase: " + listAddress.at(j).broadcast().toString() + "\n";
        }
    }
    QMessageBox::warning(this, tr("Detail"), detail);
}
