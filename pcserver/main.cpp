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
#include "mainwindow.h"
#include "utils.h"
#include "xmlparser.h"

SettingInfo settingInfo;    // 全局的系统配置定义
SessionInfo sessionInfo;    // 全局的会话定义

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

    // 连接数据库，失败则不启动程序
    DbMySQL db;
    if (!db.connectMySQL()) {
        return 1;
    }

    // 从数据库获取设置信息
    if (db.getAdminInfo() == false) {
        return 1;
    }

    // 添加启动logo
    QSplashScreen *splash = new QSplashScreen;

    splash->setPixmap(QPixmap(":/res/images/logo.png"));
    splash->show();

    MainWindow *mainwindow = new MainWindow;
    // sleep 1s for start logo
    Utils::Sleep(1000);

    // 显示主窗口
    mainwindow->show();

    // 关闭启动画面
    splash->finish(mainwindow);
    delete splash;

    return app.exec();
}
