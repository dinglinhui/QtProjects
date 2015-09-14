#include "dbmysql.h"
#include "logdock.h"
#include "utils.h"

// 全局的系统配置声明
extern SessionInfo sessionInfo;
extern SettingInfo settingInfo;

DbMySQL::DbMySQL()
{

}

DbMySQL::~DbMySQL()
{

}

bool DbMySQL::connectMySQL()
{
    QSqlDatabase db  = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("db_pcserver");
    db.setUserName("root");
    db.setPassword("root");
    settingInfo.dbName = QString("db_pcserver");
    settingInfo.dbUserName = QString("root");
    settingInfo.dbPasswd = QString("root");

    //检测数据库是否链接成功
    if(!db.open())
    {
        bool isInput;
        QString ipInput = QInputDialog::getText(NULL, QObject::tr("连接数据库服务器"),
                                                QObject::tr("请输入数据库服务器IP："), QLineEdit::Normal,
                                                QObject::tr("127.0.0.1"), &isInput);

        if (isInput && !ipInput.isEmpty()) {
            db.setHostName(ipInput);
        } else {
            QMessageBox::critical(NULL, QObject::tr("输入错误"), QObject::tr("服务器IP输入错误，程序即将退出。"));
            return false;
        }

        if(!db.open()) {
            QMessageBox::critical(NULL, QObject::tr("连接数据库错误"), db.lastError().text());
            qDebug()<<db.lastError()<<endl;
//            LogDock::appendLog(db.lastError().text());
            return false;
        } else {
            settingInfo.dbHostName = ipInput;
        }
    } else {
        settingInfo.dbHostName = "127.0.0.1";
    }
    qDebug()<<"Connect database Ok"<< endl;
//    LogDock::appendLog("Connect database Ok");
    return true;
}

bool DbMySQL::getAdminInfo()
{
    QString strSql = QString("select admin_id, admin_name, admin_level, admin_passwd from tb_admin");

    QSqlQuery query(strSql);
    if (!query.isActive()) {
        QMessageBox::warning(NULL, QObject::tr("数据库错误"), query.lastError().text());
        return false;
    }

    if (!query.next()) {
        QMessageBox::warning(NULL, QObject::tr("没有找到相关信息"), QObject::tr("数据库无系统设置，请联系DBA。"));
        return false;
    } else {
        sessionInfo.sessionId.adminId         = query.value(0).toString();
        sessionInfo.sessionId.adminName       = query.value(1).toInt();
        sessionInfo.sessionId.adminLevel      = query.value(2).toString();
        sessionInfo.sessionId.adminPasswd     = query.value(3).toString();
    }

    return true;
}

bool DbMySQL::createExamTable()
{
    QString info = QDate::currentDate().toString("yyyyMM");
    const QString tb_user = QString("tb_user_%1").arg(info);
    const QString tb_user_exam = QString("tb_user_exam_%1").arg(info);
    const QString creatUserSql = QString("CREATE TABLE `%1` ("\
                                         "`id` int(11) NOT NULL AUTO_INCREMENT,"\
                                         "`user_id` varchar(45) DEFAULT NULL,"\
                                         "`user_authorithy` varchar(45) DEFAULT NULL,"\
                                         "`user_name` varchar(45) DEFAULT NULL,"\
                                         "`user_password` varchar(45) DEFAULT NULL,"\
                                         "`exam_score` varchar(45) DEFAULT NULL,"\
                                         "PRIMARY KEY (`id`)"\
                                         ") ENGINE=InnoDB DEFAULT CHARSET=utf8;").arg(tb_user);
    const QString creatUserExamSql = QString("CREATE TABLE `%1` ("\
                                             "`id` int(11) NOT NULL AUTO_INCREMENT,"\
                                             "`user_id` varchar(45) DEFAULT NULL,"\
                                             "`user_opearte` varchar(45) DEFAULT NULL,"\
                                             "PRIMARY KEY (`id`)"\
                                             ") ENGINE=InnoDB DEFAULT CHARSET=utf8;").arg(tb_user_exam);

    QList<QString> tables;
    if(showTables(QString("tb_user%\\_%1").arg(info), tables)) {
        if(!tables.contains(tb_user)){
            if(!createTable(creatUserSql, tb_user)) {
                return false;
            }
        }

        if(!tables.contains(tb_user_exam)) {
            if(!createTable(creatUserExamSql, tb_user_exam)) {
                return false;
            }
        }
        sessionInfo.userTables << tb_user << tb_user_exam;

    } else {
        if (!createTable(creatUserSql, tb_user)) {
            return false;
        } else {
            if(!createTable(creatUserExamSql, tb_user_exam)) {
                return false;
            } else {
                sessionInfo.userTables << tb_user << tb_user_exam;
            }
        }
    }

    QString strTables;
    qDebug() << "tables:";
    std::for_each(std::begin(sessionInfo.userTables), std::end(sessionInfo.userTables), [&strTables](const QString table) {
        qDebug() << table;
        strTables.append(table).append(",");
    });
//    LogDock::appendLog(QString("Use tables(%1)").arg(strTables));
    return true;
}

bool DbMySQL::createTable(const QString &strSql, const QString &tablename)
{
    QSqlQuery query(strSql);
    qDebug() << strSql;
    if (!query.isActive()) {
        QMessageBox::warning(NULL, QObject::tr("创建表格错误"), query.lastError().text());
        return false;
    } else {
        qDebug() << QString("创建表格%1成功").arg(tablename);
    }
    return true;
}

bool DbMySQL::showTables(const QString &tablename, QList<QString>& tables)
{
    QString strSql = QString("SHOW TABLES LIKE '%1'").arg(tablename);
    qDebug() << strSql;
    QSqlQuery query(strSql);
    if (!query.isActive()) {
        QMessageBox::warning(NULL, QObject::tr("数据库错误"), query.lastError().text());
        return false;
    }

    if (!query.next()) {
        return false;
    } else {
        do{
            tables.append(query.value(0).toString());
        }while(query.next());
    }
    return true;
}
