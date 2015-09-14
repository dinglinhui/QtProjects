#include <QCoreApplication>
#include <QEventLoop>
#include <QTextStream>
#include <QTime>
#include <QDir>
#include <QFile>
#include "utils.h"

Utils::Utils()
{

}

Utils::~Utils()
{

}

void Utils::Sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void Utils::MessageHandler(QtMsgType type, const QMessageLogContext &context,const QString & msg)
{
    QString txt;
    switch (type) {
    //调试信息提示
    case QtDebugMsg:
        //            txt = QString("%1: Debug: at:%2,%3 on %4; %5").arg(QTime::currentTime().toString("hh:mm:ss.zzz"))
        //                    .arg(context.file).arg(context.line).arg(context.function).arg(msg);
        txt = msg;
        break;

        //一般的warning提示
    case QtWarningMsg:
        txt = QString("%1:Warning: at:%2,%3 on %4; %5").arg(QTime::currentTime().toString("hh:mm:ss.zzz"))
                .arg(context.file).arg(context.line).arg(context.function).arg(msg);
        break;
        //严重错误提示
    case QtCriticalMsg:
        txt = QString("%1:Critical: at:%2,%3 on %4; %5").arg(QTime::currentTime().toString("hh:mm:ss.zzz"))
                .arg(context.file).arg(context.line).arg(context.function).arg(msg);
        break;
        //致命错误提示
    case QtFatalMsg:
        txt = QString("%1:Fatal: at:%2,%3 on %4; %5").arg(QTime::currentTime().toString("hh:mm:ss.zzz"))
                .arg(context.file).arg(context.line).arg(context.function).arg(msg);
        abort();
    }
    QFile outFile(QString("%1/%2.txt").arg(QDir::currentPath()).arg(QDate::currentDate().toString("yyyy-MM-dd")));
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}

