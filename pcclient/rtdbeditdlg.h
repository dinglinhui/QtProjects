#ifndef RTDBEDITDLG_H
#define RTDBEDITDLG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
QT_END_NAMESPACE

class TestTab: public QWidget
{
Q_OBJECT

public:
	TestTab(QWidget *parent = 0);
};

class RtdbEditDlg: public QDialog
{
Q_OBJECT

public:
	RtdbEditDlg(QWidget *parent = 0);

private:
	TestTab *m_pTestTab;

	QTabWidget *tabWidget;
	QDialogButtonBox *buttonBox;
};

#endif // COMMCFGDLG_H
