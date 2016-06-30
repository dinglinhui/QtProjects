#include <QApplication>
#include <QTranslator>
#include <QSplashScreen>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QMessageBox>
#include <QDebug>

//#ifndef Q_OS_WIN
//#include "3rdparty/eventdispatcher_libev/eventdispatcher_libev.h"
//#endif

#include "dbmysql.h"
//#include "mainwindow.h"
#include "logindialog.h"
//#include "networkinformation.h"
#include "utils.h"
#include "xmlparser.h"

SettingInfo settingInfo;    // 全局的系统配置定义
SessionInfo sessionInfo;    // 全局的会话定义
DbMySQL db;

int main(int argc, char *argv[])
{
    settingInfo.sysName = PCSERVER_NAME;
    settingInfo.sysVersion = PCSERVER_VERSION;
    settingInfo.sysDate = PCSERVER_DATE;

    // 处理消息
//    qInstallMessageHandler(Utils::MessageHandler);
//#ifndef Q_OS_WIN
//    QCoreApplication::setEventDispatcher(new EventDispatcherLibEv());
//#endif

    // 处理中文乱码问题
    QTextCodec *pCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(pCodec);
    //
    QApplication app(argc, argv);

    //加载Qt自带的控件汉化文件
    QTranslator translator;

    translator.load(":/res/language/qt_zh_CN.qm");
    app.installTranslator(&translator);

    //检测USB加密模块
//    if(!EncryptModule) {
//        return 1;
//    }

    // 连接数据库，失败则不启动程序
    if (!db.connectMySQL()) {
        return 1;
    }

    // 添加启动logo
    QSplashScreen *splash = new QSplashScreen;

    splash->setPixmap(QPixmap(":/res/images/logo.png"));
    splash->show();

//    MainWindow *mainwindow = new MainWindow;
    LoginDialog *login = new LoginDialog;
    Utils::Sleep(1000);// sleep 1s for start logo
    login->show();
//    mainwindow->show();

//    NetworkInformation *network = new NetworkInformation;
//    network->show();

//    QByteArray a = QString("admin").toLocal8Bit().toBase64();
//    QString newStr(a);
//    qDebug() << newStr << " " << QTextCodec::codecForName("GBK")->toUnicode(QByteArray::fromBase64(newStr.toLocal8Bit()));;

    // 关闭启动画面
//    splash->finish(mainwindow);
    splash->finish(login);
    delete splash;

    return app.exec();
}
