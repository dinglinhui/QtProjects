#ifndef PrimeDialog_H
#define PrimeDialog_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPainter>

class PrimeDialog: public QDialog {
    Q_OBJECT
public:
    PrimeDialog(QWidget* = 0);
    ~PrimeDialog();

public slots:
    virtual void calculate();

private:
    QLineEdit* primeEdit;
    QLabel* showLabel;
};

#endif // PrimeDialog_H
