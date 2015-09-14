#ifndef UTILS_H
#define UTILS_H
#include <QString>

// 系统设置的结构
typedef struct def_SettingInfo
{
    QString sysName;            //系统名称
    QString sysVersion;         //系统版本
    QString sysDate;            //系统发布日期
    QString dbHostName;         //数据库域名
    QString dbName;             //数据库名称
    QString dbUserName;         //数据库用户名
    QString dbPasswd;           //数据库密码
}SettingInfo;

typedef struct def_AdminInfo
{
    QString adminId;            // 管理员ID
    QString adminName;          // 管理员名称
    QString adminLevel;         // 管理员等级
    QString adminPasswd;        // 管理员密码
}AdminInfo;

typedef struct def_UserInfo
{
    QString userId;            // 用户ID
    QString userAuth;          // 用户权限
    QString userName;          // 用户名
    QString userPasswd;        // 用户密码
    QString examScore;         // 考试成绩
}UserInfo;

typedef struct def_ExamInfo
{
    QString userId;             // 用户ID
    QList<QString> userOpearte; // 用户操作
}ExamInfo;

typedef struct def_SessionInfo
{
    AdminInfo sessionId;     // 会话Id
    QList<QString> userTables;  // 用户相关表格
}SessionInfo;

typedef struct tag_SERVER_INFO
{
    QString ipAddress;
    QString listenPort;
} SERVER_INFO;

class Utils
{
private:
    Utils();
    ~Utils();

public:
    static void Sleep(unsigned int msec);
    static void MessageHandler(QtMsgType type, const QMessageLogContext &context,const QString & msg);
};

#endif // UTILS_H
