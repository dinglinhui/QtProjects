#include "primedialog.h"
#include "pcdefs.h"
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <cmath>    // for sqrt()

PrimeDialog::PrimeDialog(QWidget* parent) :
    QDialog(parent) {

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::blue);
    QLabel* remindLabel = new QLabel;
    remindLabel->setText(QString(tr("请给定一个大数")));
    QLabel* primeLabel = new QLabel(tr("大数:"));
    primeLabel->setPalette(pe);
    primeEdit = new QLineEdit;
    showLabel = new QLabel;

    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(remindLabel,  0, 0, 1, 4);
    gridLayout->addWidget(primeLabel,   1, 0, 1, 1, Qt::AlignLeft);
    gridLayout->addWidget(primeEdit,    1, 1, 1, 3);
    gridLayout->addWidget(showLabel,    2, 0, 1, 4);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(CALCULATE);
    buttonBox->button(QDialogButtonBox::Cancel)->setText(CANCEL);
    buttonBox->setCenterButtons(true);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(calculate()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout* dlgLayout = new QVBoxLayout;
    dlgLayout->setMargin(10);
    dlgLayout->addLayout(gridLayout);
    dlgLayout->addStretch(40);
    dlgLayout->addWidget(buttonBox);
    this->setLayout(dlgLayout);
    this->setFixedSize(300,200);
    this->setWindowTitle(PRIME_TEST);
}

PrimeDialog::~PrimeDialog() {
    delete primeEdit;
}

inline bool IsPrime( int number ) {
    if ( ( (!(number & 1)) && number != 2 ) || (number < 2) || (number % 3 == 0 && number != 3) )
        return (false);

    for( int k = 1; 36*k*k-12*k < number;++k)
        if ( (number % (6*k+1) == 0) || (number % (6*k-1) == 0) )
            return (false);
    return true;
}

void PrimeDialog::calculate() {
    bool bPrime = IsPrime(primeEdit->text().toInt());
    showLabel->setText(QString("Number ")
                       .append(primeEdit->text())
                       .append(" is ")
                       .append(bPrime?"":"not ")
                       .append("prime number!"));
}

