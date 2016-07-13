#ifndef NETWORKINFORMATION_H
#define NETWORKINFORMATION_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class NetworkInformation: public QDialog {
    Q_OBJECT

private:
    QLabel *nameLabel;
    QLabel *ipLabel;
    QLineEdit *nameEdit;
    QLineEdit *ipEdit;
    QPushButton *detailButton;

public:
    NetworkInformation(QWidget *parent = 0);

private slots:
    void slotDetail();
};

#endif // NETWORKINFORMATION_H
