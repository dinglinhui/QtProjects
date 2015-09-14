#include <QtGui>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QLabel>
#include <QDialogButtonBox>
#include "rtdbeditdlg.h"
#include "pcdefs.h"

RtdbEditDlg::RtdbEditDlg(QWidget *parent) :
        QDialog(parent)
{
    tabWidget = new QTabWidget;
    m_pTestTab = new TestTab();
    tabWidget->addTab(m_pTestTab, RTDB_TEST);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    this->setLayout(mainLayout);

    this->setWindowTitle(RTDB_TEST);
}

TestTab::TestTab(QWidget *parent) :
        QWidget(parent)
{
    QFont font;
    font.setPointSize(12);
    QLabel *ownerLabel = new QLabel(tr("该功能正在开发中！"));
    ownerLabel->setFont(font);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(ownerLabel);
    setLayout(mainLayout);
}
