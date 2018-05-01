#ifndef PCCDEFS_H
#define PCCDEFS_H

#include <QTextCodec>
#include <QtDebug>
#include <QDate>
#include <QDir>
//
#define PCSERVER_NAME           QString("PCServer")
#define PCSERVER_VERSION        QString("V2.0.1.0")
#define PCSERVER_DATE           QDate::currentDate().toString("yyyyMMdd")
#define PCSERVER_HOMEDIR        QDir::currentPath()
#define PCSERVER_CONFIG_FILE    PCSERVER_HOMEDIR.append("/pcserver.config")
#define PCSERVER_AUTHOR         QStringLiteral("Kevin Ding")
#define PCSERVER_EMAIL          QStringLiteral("dinglinhui@hotmail.com")
#define PCSERVER_CONTEXT  		QStringLiteral("%1-%2-%3").arg(PCSERVER_NAME).arg(PCSERVER_VERSION).arg(PCSERVER_DATE)
//
#define WELCOME_CONTEXT  		QStringLiteral("%1-%2-%3").arg(PCSERVER_NAME).arg(PCSERVER_VERSION).arg(PCSERVER_DATE)
#define PCSERVER_WELCOME  		QStringLiteral("WELCOME")
#define PCSERVER_READY  		QStringLiteral("READY")
#define PCSERVER_ADMIN          QStringLiteral("CURRENT USER:")
#define ADMIN_LOGIN_DATE        QStringLiteral("LOGIN DATETIME:")
#define ADMIN_LAST_LOGIN_DATE   QStringLiteral("LAST LOGIN DATETIME")
#define PCSERVER_FILE_SAVED 	QStringLiteral("FILE SAVED")
#define GENERAL_CONFIG  		QStringLiteral("GENERAL CONFIG")
#define SYSTEM_CONFIG           QStringLiteral("SYSTEM CONFIG")
#define APPLICATION_CONFIG  	QStringLiteral("APPLICATION CONFIG")

#define RTDB_TEST  				QStringLiteral("RTDB TEST")
#define RTDB_DATAINFO  			QStringLiteral("RTDB DATAINFO")

#define MENU_SERVICE  			QStringLiteral("Service")
#define MENU_FUNCTION  			QStringLiteral("Function")
#define MENU_INTERFACE  		QStringLiteral("Interface")
#define MENU_HELP  				QStringLiteral("Help")
//
#define PCSERVER_CONFIG         QStringLiteral("PCServer CONFIG")
#define COMMUNICATION_CONFIG  	QStringLiteral("CONFIG")
#define COMMUNICATION_PACKET  	QStringLiteral("PACKET")
#define DATABASE_CONFIG         QStringLiteral("DATABASE CONFIG")
#define ROLLING_START  			QStringLiteral("ROLLING START")
#define ROLLING_STOP  			QStringLiteral("ROLLING STOP")
#define RTDB_TYPE  				QStringLiteral("RTDB Type")
#define RTDB_DATA  				QStringLiteral("RTDB Data")
#define RTDB_REFRESH_ALL  		QStringLiteral("REFRESH ALL")
#define RTDB_REFRESH_SINGLE  	QStringLiteral("REFRESH SINGLE")
#define RTDB_SAVE  				QStringLiteral("Save RTDB")
#define EXAMINATION_MANAGE      QStringLiteral("Examination")
#define COMMUNICATION_MANAGE    QStringLiteral("Communication")
#define GRAPH_CONTROL           QStringLiteral("Graph")
#define PRIME_TEST              QStringLiteral("Prime")
#define EXAM_LIST               QStringLiteral("Exam List")
#define SOE_BUFFER              QStringLiteral("SOE Buffer")
#define FULL_SCREEN      		QStringLiteral("Full Screen")
#define PCSERVER_ABOUT  		QStringLiteral("About PCServer")
#define PCSERVER_QUIT  			QStringLiteral("Quit")
#define ABOUT_CONTEXT           QStringLiteral("<i>PCServer</i> is high performance communication application." \
    "<br/><i>V1.0.0.0</i>: Build GUI Framework using Qt5." \
    "<br/><i>V2.0.1.0</i>: Added Communication Module." \
    "<br/><i>V3.0.0.0</i>: refactor Application Architecture." \
    "<br/><br/>Kevin Ding Reserved <b>dinglinhui@hotmail.com</b>")

#define COMMUNICATION_FUNCTION      QStringLiteral("Communication")
#define COMMUNICATION_CONNECT  		QStringLiteral("Connect")
#define COMMUNICATION_DISCONNECT  	QStringLiteral("Disconnect")
#define COMMUNICATION_CALL          QStringLiteral("Call Transmit")
#define TRANSMIT_PRINT              QStringLiteral("Print Transmit Table")
#define TRANSMIT_EXPORT_EXCEL       QStringLiteral("Export Excel")
#define TRANSMIT_EXPORT_CSV         QStringLiteral("Export CSV")
//
#define COMMUNICATION_IP            QStringLiteral("IP Address")
#define COMMUNICATION_LISTENPORT  	QStringLiteral("Listening port")
#define COMMUNICATION_SRCPORT       QStringLiteral("Src Port")
#define COMMUNICATION_DESTPORT      QStringLiteral("Dest Port:")
#define COMMUNICATION_TCPPORT       QStringLiteral("Transmit Port:")

#define LOGPRINT_HEADER             QStringLiteral("Log")
#define LOGPRINT_DATE               QStringLiteral("Date")
#define LOGPRINT_CONTEXT            QStringLiteral("Content")
//
#define DATATYPE_INT                QStringLiteral("Integer")
#define DATATYPE_FLOAT              QStringLiteral("Float")
#define DATATYPE_STRING 			QStringLiteral("String")

#define COMMPKT_PACKET_ANALYZE      QStringLiteral("Analyse Packet")
#define COMMPKT_SYSTEM_LOG          QStringLiteral("Sysem Log")
#define COMMPKT_SEND                QStringLiteral("Send")
#define COMMPKT_RECV                QStringLiteral("Recv")
//
#define QUIT_TITLE                  QStringLiteral("Quit %1%2").arg(PCSERVER_NAME).arg("?")
#define QUIT_TEXT                   QStringLiteral("Quit %1%2").arg(PCSERVER_NAME).arg("?")
#define CALCULATE                   QStringLiteral("calculate")
#define CONFIRM                     QStringLiteral("Confirm")
#define CANCEL                      QStringLiteral("Cancel")
#define YES                         QStringLiteral("Yes")
#define NO                          QStringLiteral("No")
#define CLOSE                       QStringLiteral("Close")

//
#define COMMPKT_POPMENU_CLEAR			QStringLiteral("clear")
#define COMMPKT_POPMENU_SAVEPACKET		QStringLiteral("save")
#define COMMPKT_POPMENU_ANALYZE			QStringLiteral("analyse")
//
#define RTDBINFO_POPMENU_REFRESHALL		QStringLiteral("refresh all")
#define RTDBINFO_POPMENU_REFRESHSINGLE	QStringLiteral("refresh single")
#define RTDBINFO_POPMENU_SAVERTDB		QStringLiteral("save RTDB")
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
#define CHANNEL_MAX    		1024
#define IED_MAX             4
#define HEADNUMBER    		26
#define BUFFSIZE      		1024
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

typedef enum tag_AUTHORITY {
    INDEX_AUTHORITY_ROOT = 0,
    INDEX_AUTHORITY_ADMIN,
    INDEX_AUTHORITY_TEACHER,
    INDEX_AUTHORITY_FORBID,
    INDEX_AUTHORITY_MAX_NUM
} AUTHORITY;

#define STRING_ADMIN_AUTHORITY_ROOT                  QStringLiteral("root")
#define STRING_ADMIN_AUTHORITY_ADMIN                 QStringLiteral("administrator")
#define STRING_ADMIN_AUTHORITY_TEACHER               QStringLiteral("teacher")
#define STRING_ADMIN_AUTHORITY_FORBID                QStringLiteral("forbid")
const QString table_authority[] = {
    STRING_ADMIN_AUTHORITY_ROOT,
    STRING_ADMIN_AUTHORITY_ADMIN,
    STRING_ADMIN_AUTHORITY_TEACHER,
    STRING_ADMIN_AUTHORITY_FORBID
};

typedef enum tag_EXAM_STATUS {
    INDEX_EXAM_STATUS_PREPARED = 0,
    INDEX_EXAM_STATUS_STARTING,
    INDEX_EXAM_STATUS_FINISED,
    INDEX_EXAM_STATUS_MAX_NUM
} EXAM_STATUS;
#define STRING_EXAM_STATUS_PREPARED                  QStringLiteral("PREPARED")
#define STRING_EXAM_STATUS_STARTING                  QStringLiteral("STARTING")
#define STRING_EXAM_STATUS_FINISED                   QStringLiteral("FINISED")

const QString table_exam_status[] = {
    STRING_EXAM_STATUS_PREPARED,
    STRING_EXAM_STATUS_STARTING,
    STRING_EXAM_STATUS_FINISED
};

typedef enum tag_EXAMINATION {
    INDEX_EXAMINATION_ID = 0,//ID
    INDEX_EXAMINATION_DATE,
    INDEX_EXAMINATION_STATUS,
    INDEX_EXAMINATION_NAME,
    INDEX_EXAMINATION_MAX_NUM
} EXAMINATION;
#define STRING_EXAMINATION_ID                  QStringLiteral("ID")
#define STRING_EXAMINATION_DATE                QStringLiteral("DATE")
#define STRING_EXAMINATION_STATUS              QStringLiteral("STATUS")
#define STRING_EXAMINATION_NAME                QStringLiteral("NAME")

typedef enum tag_COMMUNICATION {
    INDEX_COMMUNICATION_ID = 0,
    INDEX_COMMUNICATION_NAME,
    INDEX_COMMUNICATION_DATETIME,
    INDEX_COMMUNICATION_DIRECTION,
    INDEX_COMMUNICATION_CONTENT,
    INDEX_COMMUNICATION_MAX_NUM
} COMMUNICATION;
#define STRING_COMMUNICATION_ID                  QStringLiteral("ID")
#define STRING_COMMUNICATION_NAME                QStringLiteral("NAME")
#define STRING_COMMUNICATION_DATETIME            QStringLiteral("DATETIME")
#define STRING_COMMUNICATION_DIRECTION           QStringLiteral("DIRECTION")
#define STRING_COMMUNICATION_CONTENT             QStringLiteral("CONTENT")

typedef enum tag_PACKET_DIRECTION {
    PACKET_SEND = 0,
    PACKET_RECV,
} PACKET_DIRECTION;

typedef enum tag_TABLE_LOG {
    LOG_DATE = 0,
    LOG_CONTEXT,
    LOG_MAX_NUM
} TABLE_LOG;

typedef enum tag_LINKINFO {
    LINKINFO_CONNECTED = 0,
    LINKINFO_DISCONNECTED,
    LINKINFO_MAX_NUM
} LINKINFO;

typedef struct tag_COMPORT_INFO {
    QString portName;
    QString baudRate;
    QString dataBit;
    QString stopBit;
    QString parity; /*2:none;1:odd;0:even */
} COMPORT_INFO;


typedef struct tag_TCPPORT_INFO {
    QString localIP;
    QString remoteIP;
    QString remotePort;
    QString localPort;
    QString isServer;
} TCPPORT_INFO;

typedef struct tag_UDPPORT_INFO {
    QString localIP;
    QString remoteIP;
    QString remotePort;
    QString localPort;
} UDPPORT_INFO;

#endif // PCSERVER_H
