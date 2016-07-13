#ifndef DBMYSQL_H
#define DBMYSQL_H
#include <QString>
#include <QtSql>
#include <QInputDialog>
#include <QMessageBox>

class DbMySQL {
public:
    explicit DbMySQL();
    ~DbMySQL();

    //signals:
    //    void logSignal(const QString &);

public:
    bool connectMySQL();
    // tb_system
    bool getSystemInfo(const QString &adminId);
    bool updateSystemInfo(const QString &adminId);
    // tb_admin
    bool getAdminInfo(const QString &adminId, const QString &passwd);
    bool updateAdminInfo();
    // tb_exam
    bool getExamInfo(QList<QStringList> &exams);
    // 创建考试相关信息表
    bool createExamTable();
    // 创建表格
    bool createTable(const QString &strSql, const QString &tablename);
    // 列出表格
    bool showTables(const QString &tablename, QList<QString>& tables);
};

#endif // DBMYSQL_H
