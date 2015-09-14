#ifndef PAGES_H
#define PAGES_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE

class ConfigurationPage: public QWidget
{
	Q_OBJECT
public:
	ConfigurationPage(QWidget *parent = 0);

public slots:
	void changeCommPage(int id);

private:
	QStackedWidget *commcfgWidget;
};

class UpdatePage: public QWidget
{
	Q_OBJECT
public:
	UpdatePage(QWidget *parent = 0);
};

class ComPage: public QWidget
{
public:
	ComPage(QWidget *parent = 0);
};

class NetPage: public QWidget
{
public:
	NetPage(QWidget *parent = 0);
};

#endif
