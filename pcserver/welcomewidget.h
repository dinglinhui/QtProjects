#ifndef WelcomeWidget_H
#define WelcomeWidget_H

#include <QWidget>
#include <QImage>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
class QLabel;
class QImage;
class QVBoxLayout;
QT_END_NAMESPACE

class WelcomeWidget : public QWidget
{
    Q_OBJECT
public:
    WelcomeWidget(QWidget *parent = 0);
    virtual ~WelcomeWidget();

public slots:
    void addEntry();
    void resizeEvent(QResizeEvent *event);

signals:
    void sendDetails(QString name, QString address);

private:
//    QLabel *welcomLabel;
//    QVBoxLayout *mainLayout;
    QImage _image;
};

#endif
