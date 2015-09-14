#include <QtGui>
#include <QLabel>
#include "welcometab.h"
#include "pcdefs.h"

WelcomeTab::WelcomeTab(QWidget *parent):
    QWidget(parent)
{
    _image.load(":/system/images/welcome.jpg");
    this->setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(_image));
    this->setPalette(palette);
    //
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    welcomLabel = new QLabel(WELCOME_CONTEXT);
    welcomLabel->setFont(font);
    //
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(welcomLabel);
    //
    setLayout(mainLayout);
}

WelcomeTab::~WelcomeTab()
{
}

void WelcomeTab::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    QPalette pal(palette());
    pal.setBrush(QPalette::Window, QBrush(_image.scaled(event->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    this->setPalette(pal);
}

void WelcomeTab::addEntry()
{
}
