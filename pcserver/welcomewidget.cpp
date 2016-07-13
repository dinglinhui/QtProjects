#include <QtGui>
#include <QLabel>
#include "welcomewidget.h"
#include "pcdefs.h"

WelcomeWidget::WelcomeWidget(QWidget *parent):
    QWidget(parent) {
    _image.load(":/res/images/welcome.jpg");
    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(_image));
    this->setPalette(palette);
//    //
//    QFont font;
//    font.setPointSize(20);
//    font.setBold(true);
//    welcomLabel = new QLabel(WELCOME_CONTEXT);
//    welcomLabel->setFont(font);
//    //
//    mainLayout = new QVBoxLayout;
//    mainLayout->addWidget(welcomLabel);
//    //
//    setLayout(mainLayout);
}

WelcomeWidget::~WelcomeWidget() {
}

void WelcomeWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    QPalette pal(palette());
    pal.setBrush(QPalette::Window, QBrush(_image.scaled(event->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(pal);
}

void WelcomeWidget::addEntry() {
}
