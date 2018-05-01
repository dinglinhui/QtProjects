#ifndef UTILS_H
#define UTILS_H
#include <QString>

typedef struct def_SettingInfo {
    QString sysName;
    QString sysVersion;
    QString sysDate;
    QString dbHostName;
    QString dbName;
    QString dbUserName;
    QString dbPasswd;
}SettingInfo;

typedef struct tag_ServerInfo {
    QString ipAddress;
    QString listenPort;
}ServerInfo;

typedef struct def_SystemInfo {
    SettingInfo settingInfo;
    ServerInfo serverInfo;
}SystemInfo;

typedef struct def_AdminInfo {
    QString adminId;
    QString adminName;
    int adminLevel;
    QString adminPasswd;
    QString adminLoginDate;
}AdminInfo;

typedef struct def_UserInfo {
    QString userId;
    QString userAuth;
    QString userName;
    QString userPasswd;
    QString examScore;
}UserInfo;

typedef struct def_ExamInfo {
    QString userId;
    QList<QString> userOpearte;
}ExamInfo;

typedef struct def_SessionInfo {
    SystemInfo systemInfo;
    AdminInfo sessionId;
    QList<QString> userTables;
}SessionInfo;

class Utils {
private:
    Utils();
    ~Utils();

public:
    static void Sleep(unsigned int msec);
    static void MessageHandler(QtMsgType type, const QMessageLogContext &context,const QString & msg);
};

#endif // UTILS_H
