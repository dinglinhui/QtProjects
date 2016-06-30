#ifndef PCCDEFS_H
#define PCCDEFS_H

#include <QTextCodec>
#include <QtDebug>
#include <QDate>
#include <QDir>
//
#define PCSERVER_NAME           QString("PCServer")
#define PCSERVER_VERSION        QString("V1.0.1.0")
#define PCSERVER_DATE           QDate::currentDate().toString("yyyyMMdd")
#define PCSERVER_HOMEDIR        QDir::currentPath()
#define PCSERVER_CONFIG_FILE    PCSERVER_HOMEDIR.append("/pcserver.config")
#define PCSERVER_AUTHOR         QStringLiteral("丁林辉")
#define PCSERVER_EMAIL          QStringLiteral("dinglinhui@hotmail.com")
#define PCSERVER_CONTEXT  		QStringLiteral("%1-%2-%3").arg(PCSERVER_NAME).arg(PCSERVER_VERSION).arg(PCSERVER_DATE)
//
#define WELCOME_CONTEXT  		QStringLiteral("%1-%2-%3").arg(PCSERVER_NAME).arg(PCSERVER_VERSION).arg(PCSERVER_DATE)
#define PCSERVER_WELCOME  		QStringLiteral("欢迎首页")
#define PCSERVER_READY  		QStringLiteral("准备")
#define PCSERVER_ADMIN          QStringLiteral("当前登录用户:")
#define ADMIN_LOGIN_DATE        QStringLiteral("登录时间:")
#define ADMIN_LAST_LOGIN_DATE   QStringLiteral("上次登录时间:")
#define PCSERVER_FILE_SAVED 	QStringLiteral("文件已保存")
#define GENERAL_CONFIG  		QStringLiteral("通用配置")
#define SYSTEM_CONFIG           QStringLiteral("系统配置")
#define APPLICATION_CONFIG  	QStringLiteral("应用配置")

#define RTDB_TEST  				QStringLiteral("实时库测试")
#define RTDB_DATAINFO  			QStringLiteral("单点信息")

#define MENU_SERVICE  			QStringLiteral("服务")
#define MENU_FUNCTION  			QStringLiteral("功能")
#define MENU_INTERFACE  		QStringLiteral("界面")
#define MENU_HELP  				QStringLiteral("帮助")
//
#define PCSERVER_CONFIG         QStringLiteral("PCServer配置")
#define COMMUNICATION_CONFIG  	QStringLiteral("通信配置")
#define COMMUNICATION_PACKET  	QStringLiteral("通信报文")
#define DATABASE_CONFIG         QStringLiteral("数据库配置")
#define ROLLING_START  			QStringLiteral("开始滚动")
#define ROLLING_STOP  			QStringLiteral("停止滚动")
#define RTDB_TYPE  				QStringLiteral("实时库类型")
#define RTDB_DATA  				QStringLiteral("实时库点表")
#define RTDB_REFRESH_ALL  		QStringLiteral("查全表")
#define RTDB_REFRESH_SINGLE  	QStringLiteral("查单点")
#define RTDB_SAVE  				QStringLiteral("保存实时库")
#define EXAMINATION_MANAGE      QStringLiteral("考试管理")
#define COMMUNICATION_MANAGE    QStringLiteral("通信管理")
#define EXAM_LIST               QStringLiteral("考试场次")
#define SOE_BUFFER              QStringLiteral("SOE缓存")
#define PCSERVER_ABOUT  		QStringLiteral("关于PCServer")
#define PCSERVER_QUIT  			QStringLiteral("退出")
#define ABOUT_CONTEXT           QStringLiteral("<i>PCServer</i>是XXX。" \
    "<br/><i>V1.00</i>：采用Qt5.4实现界面框架搭建。" \
    "<br/><br/>XXX有限公司  版权所有 <b>dinglinhui@hotmail.com</b>")
#define COMMUNICATION_FUNCTION      QStringLiteral("通道功能")
#define COMMUNICATION_CONNECT  		QStringLiteral("连接")
#define COMMUNICATION_DISCONNECT  	QStringLiteral("断开连接")
#define COMMUNICATION_CALL          QStringLiteral("召唤转发表")
#define TRANSMIT_PRINT              QStringLiteral("打印转发表")
#define TRANSMIT_EXPORT_EXCEL       QStringLiteral("导出Excel")
#define TRANSMIT_EXPORT_CSV         QStringLiteral("导出CSV")
//
#define COMMUNICATION_IP            QStringLiteral("IP地址：")
#define COMMUNICATION_LISTENPORT  	QStringLiteral("监听端口：")
#define COMMUNICATION_SRCPORT       QStringLiteral("源端口：")
#define COMMUNICATION_DESTPORT      QStringLiteral("目的端口：")
#define COMMUNICATION_TCPPORT       QStringLiteral("转发表端口：")

#define LOGPRINT_HEADER             QStringLiteral("日志打印")
#define LOGPRINT_DATE               QStringLiteral("日期")
#define LOGPRINT_CONTEXT            QStringLiteral("日志内容")
//
#define DATATYPE_INT                QStringLiteral("整型")
#define DATATYPE_FLOAT              QStringLiteral("浮点型")
#define DATATYPE_STRING 			QStringLiteral("字符串")

#define COMMPKT_PACKET_ANALYZE      QStringLiteral("报文分析")
#define COMMPKT_SYSTEM_LOG          QStringLiteral("系统日志")
#define COMMPKT_SEND                QStringLiteral("发送")
#define COMMPKT_RECV                QStringLiteral("接收")
//
#define QUIT_TITLE                  QStringLiteral("退出%1%2").arg(PCSERVER_NAME).arg("?")
#define QUIT_TEXT                   QStringLiteral("确定要退出%1%2").arg(PCSERVER_NAME).arg("?")
#define CONFIRM                     QStringLiteral("确定")
#define CANCEL                      QStringLiteral("取消")
#define YES                         QStringLiteral("是")
#define NO                          QStringLiteral("否")
#define CLOSE                       QStringLiteral("关闭")

//
#define COMMPKT_POPMENU_CLEAR			QStringLiteral("清空报文")
#define COMMPKT_POPMENU_SAVEPACKET		QStringLiteral("保存报文")
#define COMMPKT_POPMENU_ANALYZE			QStringLiteral("分析报文")
//
#define RTDBINFO_POPMENU_REFRESHALL		QStringLiteral("查全表")
#define RTDBINFO_POPMENU_REFRESHSINGLE	QStringLiteral("查单点")
#define RTDBINFO_POPMENU_SAVERTDB		QStringLiteral("保存修改")
//
#define XML_ELEMENT_CONFIGURATION       QStringLiteral("configuration")
#define XML_ELEMENT_SERVER              QStringLiteral("server")
#define XML_ELEMENT_ITEM                QStringLiteral("item")
#define XML_ELEMENT_IP_ADDRESS          QStringLiteral("ipaddress")
#define XML_ELEMENT_LISTEN_PORT         QStringLiteral("listenport")
#define XML_ELEMENT_KEY                 QStringLiteral("key")
#define XML_ELEMENT_VALUE               QStringLiteral("value")
#define XML_ELEMENT_IP_DEFAULT          QStringLiteral("127.0.0.1")
#define XML_ELEMENT_PORT_DEFAULT        QStringLiteral("16011")
//
#define CHANNEL_MAX    		1024                //最大通道个数
#define IED_MAX             4                   //最大装置个数
#define HEADNUMBER    		26                  //报文头的长度
#define BUFFSIZE      		1024                //缓冲区的长度
//
#define PACKET_START_FLAG  	0X68
#define SEND_RPT_START  	0X01
#define SEND_RPT_STOP   	0X02
#define PCSERVER_TEST   	0X03
#define REPORT_MESSAGE  	0X83
#define LOG_ERROR       	0X86
#define LOG_COMMAND     	0X87
#define LOG_EVENT       	0X88
#define INTGER_DATA   		0X00
#define DOUBLE_DATA   		0X01

/**********************************************************************/
typedef enum tag_AUTHORITY
{
    INDEX_AUTHORITY_ROOT = 0, //顶级权限
    INDEX_AUTHORITY_ADMIN,    //报文查看，日志跟踪等除了部分删除功能
    INDEX_AUTHORITY_TEACHER,  //启动考试，学员以及考试相关的增删该查功能
    INDEX_AUTHORITY_FORBID,   //已经被禁止的账户或者是尚未启用的账户
    INDEX_AUTHORITY_MAX_NUM
} AUTHORITY;

#define STRING_ADMIN_AUTHORITY_ROOT                  QStringLiteral("超级用户")
#define STRING_ADMIN_AUTHORITY_ADMIN                 QStringLiteral("管理员")
#define STRING_ADMIN_AUTHORITY_TEACHER               QStringLiteral("教师")
#define STRING_ADMIN_AUTHORITY_FORBID                QStringLiteral("已禁止")
const QString table_authority[] = {
    STRING_ADMIN_AUTHORITY_ROOT,
    STRING_ADMIN_AUTHORITY_ADMIN,
    STRING_ADMIN_AUTHORITY_TEACHER,
    STRING_ADMIN_AUTHORITY_FORBID
};

/**********************************************************************/
typedef enum tag_EXAM_STATUS
{
    INDEX_EXAM_STATUS_PREPARED = 0,
    INDEX_EXAM_STATUS_STARTING,
    INDEX_EXAM_STATUS_FINISED,
    INDEX_EXAM_STATUS_MAX_NUM
} EXAM_STATUS;
#define STRING_EXAM_STATUS_PREPARED                  QStringLiteral("未开始")
#define STRING_EXAM_STATUS_STARTING                  QStringLiteral("已开始")
#define STRING_EXAM_STATUS_FINISED                   QStringLiteral("已结束")

const QString table_exam_status[] = {
    STRING_EXAM_STATUS_PREPARED,
    STRING_EXAM_STATUS_STARTING,
    STRING_EXAM_STATUS_FINISED
};

/**********************************************************************/
typedef enum tag_EXAMINATION
{
    INDEX_EXAMINATION_ID = 0,//ID
    INDEX_EXAMINATION_DATE,  //考试日期
    INDEX_EXAMINATION_STATUS,//考试状态
    INDEX_EXAMINATION_NAME,  //考试名称
    INDEX_EXAMINATION_MAX_NUM
} EXAMINATION;
#define STRING_EXAMINATION_ID                  QStringLiteral("考试号")
#define STRING_EXAMINATION_DATE                QStringLiteral("考试日期")
#define STRING_EXAMINATION_STATUS              QStringLiteral("考试状态")
#define STRING_EXAMINATION_NAME                QStringLiteral("考试名称")

/**********************************************************************/

typedef enum tag_PACKET_DIRECTION
{
    PACKET_SEND = 0,
    PACKET_RECV,
} PACKET_DIRECTION;

typedef enum tag_TABLE_LOG
{
    LOG_DATE = 0,
    LOG_CONTEXT,
    LOG_MAX_NUM
} TABLE_LOG;

typedef enum tag_LINKINFO
{
    LINKINFO_CONNECTED = 0,
    LINKINFO_DISCONNECTED,
    LINKINFO_MAX_NUM
} LINKINFO;


///////////////////////////////////////////////////
/*
 *  定义串口通信特性
 */
typedef struct tag_COMPORT_INFO
{
    QString portName;/* 串口名 */
    QString baudRate; /* 波特率 */
    QString dataBit; /* 数据位 */
    QString stopBit; /* 停止位 */
    QString parity; /* 校验：2:none;1:odd;0:even */
} COMPORT_INFO;

/*
 *  定义网络通信特性
 */
typedef struct tag_TCPPORT_INFO
{
    QString localIP;
    QString remoteIP;
    QString remotePort;
    QString localPort;
    QString isServer;
} TCPPORT_INFO;

typedef struct tag_UDPPORT_INFO
{
    QString localIP;
    QString remoteIP;
    QString remotePort;
    QString localPort;
} UDPPORT_INFO;

#endif // PCSERVER_H
