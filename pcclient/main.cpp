#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLibraryInfo>
#include <QString>
#include <QLocale>
#include <QDesktopWidget>

#include "pcclient.h"

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(pcclient);

	QApplication app(argc, argv);

	QTranslator oTranslator;
	oTranslator.load(":/qt_zh_CN");
	app.installTranslator(&oTranslator);

	QTextCodec *pCodec = QTextCodec::codecForName("System");
	QTextCodec::setCodecForLocale(pCodec);
    //QTextCodec::setCodecForCStrings(pCodec);
    //QTextCodec::setCodecForTr(pCodec);

	QFont font;
#if defined(Q_OS_WIN32)//windows	font.setPointSize(9);
	font.setBold(false);

#elif defined(Q_OS_LINUX)//linux	font.setPointSize(9);
	font.setBold(false);

#elif defined(Q_OS_SOLARIS)//solaris font.setPointSize(12);
	font.setBold(false);

#endif
	app.setFont(font);

	PCClient pcc;
	pcc.show();
	pcc.move((QApplication::desktop()->width() - pcc.width()) / 2, (QApplication::desktop()->height() - pcc.height()) / 2);
	return app.exec();
}
