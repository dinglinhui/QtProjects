#ifndef DBMYSQL_H
#define DBMYSQL_H
#include <QString>
#include <QtSql>
#include <QInputDialog>
#include <QMessageBox>

class DbMySQL
{
public:
    explicit DbMySQL();
    ~DbMySQL();

//signals:
//    void logSignal(const QString &);

public:
    // 连接数据库
    bool connectMySQL();
    // 从数据库获取系统设置信息
    bool getAdminInfo(const QString &adminId, const QString &passwd);
    bool updateAdminInfo();
    // 从数据库获取考试信息
    bool getExamInfo(QList<QStringList> &exams);
    // 创建考试相关信息表
    bool createExamTable();
    // 创建表格
    bool createTable(const QString &strSql, const QString &tablename);
    // 列出表格
    bool showTables(const QString &tablename, QList<QString>& tables);
};

#endif // DBMYSQL_H
