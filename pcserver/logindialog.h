#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPainter>

class LoginDialog: public QDialog {
    Q_OBJECT
public:
    LoginDialog(QWidget* = 0);
    ~LoginDialog();

public slots:
    virtual void accept() override;

private:
    void paintEvent(QPaintEvent *) override;

private:
    QLineEdit* usrLineEdit;
    QLineEdit* pwdLineEdit;
};

#endif // LOGINDIALOG_H
