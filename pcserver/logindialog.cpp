#include "logindialog.h"
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include "dbmysql.h"
#include "mainwindow.h"

extern DbMySQL db;

LoginDialog::LoginDialog(QWidget* parent) :
    QDialog(parent)
{
    QLabel* showLabel = new QLabel;
    QImage image(":/res/images/login.jpg");
    showLabel->setPixmap(QPixmap::fromImage(image));
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::blue);
    QLabel* usrLabel = new QLabel(tr("  帐  号:"));
    QLabel* pwdLabel = new QLabel(tr("  密  码:"));
    usrLabel->setPalette(pe);
    pwdLabel->setPalette(pe);
    usrLineEdit = new QLineEdit;
    pwdLineEdit = new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::Password);

    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(showLabel,    0, 0, 1, 4);
    gridLayout->addWidget(usrLabel,     1, 0, 1, 1, Qt::AlignLeft);
    gridLayout->addWidget(usrLineEdit,  1, 1, 1, 3);
    gridLayout->addWidget(pwdLabel,     2, 0, 1, 1, Qt::AlignLeft);
    gridLayout->addWidget(pwdLineEdit,  2, 1, 1, 3);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(CONFIRM);
    buttonBox->button(QDialogButtonBox::Cancel)->setText(CANCEL);
    buttonBox->setCenterButtons(true);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QVBoxLayout* dlgLayout = new QVBoxLayout;
    dlgLayout->setMargin(0);
    dlgLayout->addLayout(gridLayout);
    dlgLayout->addStretch(40);
    dlgLayout->addWidget(buttonBox);
    this->setLayout(dlgLayout);
    this->setFixedSize(300,200);
    this->setWindowTitle(tr("登录PCServer"));
}

LoginDialog::~LoginDialog()
{
    delete usrLineEdit;
    delete pwdLineEdit;
}

void LoginDialog::accept()
{
    // 从数据库获取设置信息
    QString newPasswd(pwdLineEdit->text().toLocal8Bit().toBase64());
    if (db.getAdminInfo(usrLineEdit->text().trimmed(), newPasswd)) {

        MainWindow *mainwindow = new MainWindow;
        mainwindow->show();

        QDialog::accept();
        this->close();
    }
    else
    {
        QMessageBox::warning(this, tr("警告"), tr("用户或密码错误！"), QMessageBox::Yes);
        usrLineEdit->setFocus();
    }
}

void LoginDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/images/background.jpg");
    painter.drawPixmap(0,0,350,250,pix);
}

