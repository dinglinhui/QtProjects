#ifndef PCCDEFS_H
#define PCCDEFS_H

#include <QTextCodec>
#include <QtDebug>

#define PCCLIENT_WELCOME  		QStringLiteral("欢迎首页")
#define WELCOME_CONTEXT  		QStringLiteral("PCClientV2.2  欢迎您!")
#define PCCLIENT_READY  		QStringLiteral("准备")
#define PCCLIENT_FILE_SAVED 	QStringLiteral("文件已保存")
#define GENERAL_CONFIG  		QStringLiteral("通用配置")
#define OTHER_CONFIG  			QStringLiteral("其它配置")
#define RTDB_TEST  				QStringLiteral("实时库测试")
#define RTDB_DATAINFO  			QStringLiteral("单点信息")

#define MENU_SERVICE  			QStringLiteral("服务")
#define MENU_FUNCTION  			QStringLiteral("功能")
#define MENU_INTERFACE  		QStringLiteral("界面")
#define MENU_HELP  				QStringLiteral("帮助")
//
#define COMMUNICATION_MASTER  	QStringLiteral("通信主站")
#define COMMUNICATION_CONFIG  	QStringLiteral("通信配置")
#define COMMUNICATION_PACKET  	QStringLiteral("通信报文")
#define ROLLING_START  			QStringLiteral("开始滚动")
#define ROLLING_STOP  			QStringLiteral("停止滚动")
#define RTDB_TYPE  				QStringLiteral("实时库类型")
#define RTDB_DATA  				QStringLiteral("实时库点表")
#define RTDB_REFRESH_ALL  		QStringLiteral("查全表")
#define RTDB_REFRESH_SINGLE  	QStringLiteral("查单点")
#define RTDB_SAVE  				QStringLiteral("保存实时库")
#define TRANSMIT_TABLE  	    QStringLiteral("通道功能")
#define TRANSMIT_MASTER         QStringLiteral("转发表")
#define SOE_BUFFER              QStringLiteral("SOE缓存")
#define PCCLIENT_ABOUT  		QStringLiteral("关于PCClient")
#define PCCLIENT_QUIT  			QStringLiteral("退出")
#define PCCLIENT_CONTEXT  		QStringLiteral("<b>PCClient</b>是电力通讯系统的配套辅助调试工具。<br/><b>V2.01</b>：采用Qt4.7.1实现界面框架搭建，增加远动实时库查看修改功能、通信报文查看功能等。<br/><b>V2.10</b>：采用Qt5.2.1重新搭建界面，增加远动101、104转发表查看，导出以及打印功能。<br/><b>V2.20</b>：增加远动101、104SOE缓存查看功能。<br/><br/>上海思源弘瑞自动化有限公司  版权所有 <b>dinglinhui@hotmail.com</b>")
#define TRANSMIT_FUNCTION  		QStringLiteral("通道功能")
#define TRANSMIT_CONNECT  		QStringLiteral("连接")
#define TRANSMIT_DISCONNECT  	QStringLiteral("断开连接")
#define TRANSMIT_CALL           QStringLiteral("召唤转发表")
#define TRANSMIT_PRINT          QStringLiteral("打印转发表")
#define TRANSMIT_EXPORT_EXCEL   QStringLiteral("导出Excel")
#define TRANSMIT_EXPORT_CSV     QStringLiteral("导出CSV")
#define IEC103_FUNCTION  		QStringLiteral("IEC103功能")
#define IEC61850_FUNCTION  		QStringLiteral("IEC61850功能")
//
#define COMMUNICATION_IP  		QStringLiteral("远动IP地址：")
#define COMMUNICATION_SRCPORT  	QStringLiteral("源端口：")
#define COMMUNICATION_DESTPORT  QStringLiteral("目的端口：")
#define COMMUNICATION_TCPPORT   QStringLiteral("转发表端口：")

//
#define COMMPKT_ID  			QStringLiteral("序号")
#define COMMPKT_MASTER  		QStringLiteral("通讯主站")
#define COMMPKT_SEND_RECV  		QStringLiteral("收发")
#define COMMPKT_TIME  			QStringLiteral("时间")
#define COMMPKT_DESC  			QStringLiteral("描述")
#define COMMPKT_PACKET  		QStringLiteral("报文")
//
#define RTDBINFO_SADDR			QStringLiteral("短地址")
#define RTDBINFO_DESC			QStringLiteral("描述")
#define RTDBINFO_DATATYPE		QStringLiteral("数据类型")
#define RTDBINFO_DATAVALUE		QStringLiteral("值")
#define RTDBINFO_EDITFLAG		QStringLiteral("修改标记")
#define EDITED_FLAG  			QStringLiteral("已修改")
//
#define DATATYPE_INT 			QStringLiteral("整型")
#define DATATYPE_FLOAT 			QStringLiteral("浮点型")
//
#define TRANSMITINFO_INDEX              QStringLiteral("序号")
#define TRANSMITINFO_INFOADDR           QStringLiteral("信息地址")
#define TRANSMITINFO_IEDADDR            QStringLiteral("装置地址")
#define TRANSMITINFO_DESC               QStringLiteral("描述")
#define TRANSMITINFO_THRESHOLD_TYPE     QStringLiteral("门槛类型")
#define TRANSMITINFO_THRESHOLD          QStringLiteral("门槛值")
#define TRANSMITINFO_OFFSET             QStringLiteral("偏移量B")
#define TRANSMITINFO_MULTIFACTOR        QStringLiteral("乘积系数K")
#define TRANSMITINFO_STATUSMODI         QStringLiteral("状态修正(1-Normal,2-Inverted)")

#define SOE_BUFFER_TYPE         QStringLiteral("SOE类型")
#define SOE_BUFFER_INDEX        QStringLiteral("序号")
#define SOE_BUFFER_OLDEST       QStringLiteral("内部编号")
#define SOE_BUFFER_DESC         QStringLiteral("SOE描述")
#define SOE_BUFFER_QUALITY      QStringLiteral("品质")
#define SOE_BUFFER_VALUE        QStringLiteral("状态")
#define SOE_BUFFER_TIME         QStringLiteral("时间")

#define COMMPKT_PACKET_ANALYZE  QStringLiteral("报文分析")
#define COMMPKT_SYSTEM_LOG  	QStringLiteral("系统日志")
//
#define COMMPKT_PACKET_MX  		QStringLiteral("遥测报文")
#define COMMPKT_PACKET_ST  		QStringLiteral("遥信报文")
#define COMMPKT_PACKET_CO  		QStringLiteral("遥控报文")
#define COMMPKT_PACKET_OTHER  	QStringLiteral("其他报文")
//
#define COMMPKT_SEND  			QStringLiteral("发送")
#define COMMPKT_RECV  			QStringLiteral("接收")
//
#define QUIT_TITLE  			QStringLiteral("退出PCClient？")
#define QUIT_TEXT  				QStringLiteral("确定要退出PCClient？")
#define CONFIRM  				QStringLiteral("确定")
#define CANCEL  				QStringLiteral("取消")
#define YES  					QStringLiteral("是")
#define NO  					QStringLiteral("否")
#define CLOSE  					QStringLiteral("关闭")

//
#define COMMPKT_POPMENU_CLEAR			QStringLiteral("清空报文")
#define COMMPKT_POPMENU_SAVEPACKET		QStringLiteral("保存报文")
#define COMMPKT_POPMENU_ANALYZE			QStringLiteral("分析报文")
//
#define RTDBINFO_POPMENU_REFRESHALL		QStringLiteral("查全表")
#define RTDBINFO_POPMENU_REFRESHSINGLE	QStringLiteral("查单点")
#define RTDBINFO_POPMENU_SAVERTDB		QStringLiteral("保存修改")
//
#define XML_ELEMENT_PCCLIENT        QStringLiteral("PCClient")
#define XML_ELEMENT_SERVERINFO      QStringLiteral("ServerInfo")
#define XML_ELEMENT_RTDBTABLE       QStringLiteral("RTDBTable")
#define XML_ELEMENT_IP              QStringLiteral("IP")
#define XML_ELEMENT_SRCPORT         QStringLiteral("SRCPORT")
#define XML_ELEMENT_DESTPORT        QStringLiteral("DESTPORT")
#define XML_ELEMENT_TRANSPORT       QStringLiteral("TRANSPORT")
#define XML_ELEMENT_TRANSENABLE  	QStringLiteral("TRANSENABLE")
#define XML_ELEMENT_MX  		QStringLiteral("MX")
#define XML_ELEMENT_ST  		QStringLiteral("ST")
#define XML_ELEMENT_CO  		QStringLiteral("CO")
#define XML_ELEMENT_SP  		QStringLiteral("SP")
#define XML_ELEMENT_SG  		QStringLiteral("SG")
#define XML_ELEMENT_SE  		QStringLiteral("SE")
//
#define IEC103_POPMENU_CREATE_CHANNEL  	QStringLiteral("创建通道")
#define IEC103_POPMENU_CREATE_CHANNEL_ATTRIBUTE  	QStringLiteral("通道属性")
#define IEC103_POPMENU_CREATE_CONNECT  	QStringLiteral("建立连接")
#define IEC103_POPMENU_CREATE_DISCONNECT  	QStringLiteral("断开连接")

//
#define CHANNEL_MAX    		10                  //最大通道个数
#define IED_MAX             4                   //最大装置个数
#define HEADNUMBER    		26                  //报文头的长度
#define BUFFSIZE      		1024                //缓冲区的长度

//
#define PACKET_START_FLAG  	0X68
#define SEND_RPT_START  	0X01
#define SEND_RPT_STOP   	0X02
#define PCCLIENT_TEST   	0X03
#define REPORT_MESSAGE  	0X83
#define LOG_ERROR       	0X86
#define LOG_COMMAND     	0X87
#define LOG_EVENT       	0X88
#define INTGER_DATA   		0X00
#define DOUBLE_DATA   		0X01

#define TABLE_MX       		0X11  //查询MX表
#define TABLE_ST       		0X12  //查询ST表
#define TABLE_CO       		0X13  //查询CO表
#define TABLE_SP       		0X14  //查询SP表
#define TABLE_SG       		0X15  //查询SG表
#define TABLE_SE       		0X16  //查询SE表
#define RECORD_MX	  		0X21  //查询MX表记录
#define RECORD_ST	  		0X22  //查询ST表记录
#define RECORD_CO	  		0X23  //查询CO表记录
#define RECORD_SP	  		0X24  //查询SP表记录
#define RECORD_SG	  		0X25  //查询SG表记录
#define RECORD_SE	  		0X26  //查询SE表记录
#define TRANSMIT_CHNL_A     0X31  //查询所有通道记录
#define TRANSMIT_CHNL_S     0X32  //查询某个通道记录
#define TRANSMIT_AI         0X33  //查询AI转发表记录
#define TRANSMIT_COS        0X34  //查询COS转发表记录
#define TRANSMIT_DO         0X35  //查询DO转发表记录
#define SOE_BUFFER_CHNL		0X41  //查询所有通道和装置记录
#define SOE_BUFFER_DATA   	0X42  //查询单通道下SOE缓存记录
#define ENDFLAG_RSP         0X90  /*结束帧*/
#define TABLE_MX_RSP    	0X91  //MX表报文
#define TABLE_ST_RSP    	0X92  //ST表报文
#define TABLE_CO_RSP    	0X93  //CO表报文
#define TABLE_SP_RSP    	0X94  //SP表报文
#define TABLE_SG_RSP    	0X95  //SG表报文
#define TABLE_SE_RSP    	0X96  //SE表报文
#define RECORD_MX_RSP   	0XA1  //MX表记录
#define RECORD_ST_RSP   	0XA2  //ST表记录
#define RECORD_CO_RSP   	0XA3  //CO表记录
#define RECORD_SP_RSP   	0XA4  //SP表记录
#define RECORD_SG_RSP   	0XA5  //SG表记录
#define RECORD_SE_RSP   	0XA6  //SE表记录
#define TRANSMIT_CHNL_A_RSP 0XB1  //所有通道记录
#define TRANSMIT_CHNL_S_RSP 0XB2  //某个通道记录
#define TRANSMIT_AI_RSP     0XB3  //AI转发表记录
#define TRANSMIT_COS_RSP    0XB4  //COS转发表记录
#define TRANSMIT_DO_RSP     0XB5  //DO转发表记录
#define TRANSMIT_END_RSP 	0XBF  //召唤结束帧
#define SOE_BUFFER_CHNL_RSP	0XC1  //所有通道和装置记录
#define SOE_BUFFER_DATA_RSP 0XC2  //单通道下SOE缓存记录
//
#ifndef NULL
#define NULL	0
#endif

#if defined(Q_OS_WIN32)//window系统
#define PCCLIENT_HOME QDir::currentPath()

#elif defined(Q_OS_LINUX)//linux系统
#define PCCLIENT_HOME QString("/home/shr/pcclient")

#elif defined(Q_OS_SOLARIS)//solaris系统
#define PCCLIENT_HOME QString("/export/home/shr/pcclient")
#else
#define PCCLIENT_HOME QDir::currentPath()
#endif

typedef enum tag_PACKET_DIRECTION
{
    PACKET_SEND = 0,
    PACKET_RECV,
} PACKET_DIRECTION;

typedef enum tag_TAB_INDEX
{
    TAB_WELCOME = 0,
    TAB_RTDBDATA,
    TAB_COMMPKT,
    TAB_TRANSMIT,
    TAB_IEC103FUNC,
    TAB_IEC61850FUNC,
    TAB_MAX_NUM
} TAB_INDEX;

typedef enum tag_TABLE_COMMPKT
{
    TABLE_COMMPKT_MASTER = 0,
    TABLE_COMMPKT_SEND_RECV,
    TABLE_COMMPKT_TIME,
    TABLE_COMMPKT_PACKET,
    TABLE_COMMPKT_MAX_NUM
} TABLE_COMMPKT;

#define TABLE_COMMPKT_PACKET_ANALYZE  TABLE_COMMPKT_PACKET+1

typedef enum tag_TABLE_RTDBINFO
{
    TABLE_RTDBINFO_SADDR = 0,
    TABLE_RTDBINFO_DESC,
    TABLE_RTDBINFO_DATATYPE,
    TABLE_RTDBINFO_DATAVALUE,
    TABLE_RTDBINFO_DATAVALUE_SRC,
    TABLE_RTDBINFO_EDITFLAG,
    TABLE_RTDBINFO_MAX_NUM
} TABLE_RTDBINFO;

typedef enum tag_RTDB
{
    RTDB_MX = 0,
    RTDB_ST,
    RTDB_CO,
    RTDB_SP,
    RTDB_SG,
    RTDB_SE,
    RTDB_MAX_NUM
} RTDB;

typedef struct tag_SERVER_INFO
{
    QString ip;
    QString srcPort;
    QString destPort;
    QString transPort;
    QString transEnable;
} SERVER_INFO;

typedef struct tag_RTDB_INFO
{
    QString rtdb[RTDB_MAX_NUM];
} RTDB_INFO;

///////////////////////////////////////////////////
typedef enum tag_TRANSMITINFO
{
    TRANSMITINFO_AI = 0,
    TRANSMITINFO_COS,
    TRANSMITINFO_DO,
    TRANSMITINFO_MAX_NUM
} TRANSMITINFO;

typedef enum tag_TRANSINFO
{
    TRANSINFO_TRANSMIT = 0,
    TRANSINFO_SOEBUFFER,
    TRANSINFO_MAX_NUM
} TRANSINFO;

typedef enum tag_TABLE_TRANSMITINFO_AI//遥测
{
    TABLE_TRANSMITINFO_AI_INDEX = 0,//序号（点号）
    TABLE_TRANSMITINFO_AI_INFOADDR,//信息地址
    TABLE_TRANSMITINFO_AI_IEDADDR,//装置地址
    TABLE_TRANSMITINFO_AI_DESC,//描述
    TABLE_TRANSMITINFO_AI_THRESHOLD_TYPE,//门槛类型
    TABLE_TRANSMITINFO_AI_THRESHOLD,//门槛值
    TABLE_TRANSMITINFO_AI_OFFSET,//偏移量B
    TABLE_TRANSMITINFO_AI_MULTIFACTOR,//乘积系数K
    TABLE_TRANSMITINFO_AI_MAX_NUM
} TABLE_TRANSMITINFO_AI;

typedef enum tag_TABLE_TRANSMITINFO_COS//遥信
{
    TABLE_TRANSMITINFO_COS_INDEX = 0,//序号（点号）
    TABLE_TRANSMITINFO_COS_INFOADDR,//信息地址
    TABLE_TRANSMITINFO_COS_IEDADDR,//装置地址
    TABLE_TRANSMITINFO_COS_DESC,//描述
    TABLE_TRANSMITINFO_COS_STATUSMODI,//状态修正
    TABLE_TRANSMITINFO_COS_MAX_NUM
} TABLE_TRANSMITINFO_COS;

typedef enum tag_TABLE_TRANSMITINFO_DO//遥控
{
    TABLE_TRANSMITINFO_DO_INDEX = 0,//序号（点号）
    TABLE_TRANSMITINFO_DO_INFOADDR,//信息地址
    TABLE_TRANSMITINFO_DO_IEDADDR,//装置地址
    TABLE_TRANSMITINFO_DO_DESC,//描述
    TABLE_TRANSMITINFO_DO_MAX_NUM
} TABLE_TRANSMITINFO_DO;

typedef enum tag_TABLE_TRANSMITINFO_SOE_BUFFER//SOE缓存
{
    TABLE_TRANSMITINFO_SOE_BUFFER_TYPE = 0,//类型
    TABLE_TRANSMITINFO_SOE_BUFFER_INDEX,//序号
    TABLE_TRANSMITINFO_SOE_BUFFER_OLDEST,//内部编号
    TABLE_TRANSMITINFO_SOE_BUFFER_DESC,//描述
    TABLE_TRANSMITINFO_SOE_BUFFER_VALUE,//值
    TABLE_TRANSMITINFO_SOE_BUFFER_QUALITY ,//品质
    TABLE_TRANSMITINFO_SOE_BUFFER_TIME,//时间
    TABLE_TRANSMITINFO_SOE_BUFFER_MAX_NUM
} TABLE_TRANSMITINFO_SOE_BUFFER;

/* 远动时间结构 */
typedef struct
{
    unsigned short int    mSecsAndSecs;   /* 0 to 59,999                              */
                                 /* store seconds with milliseconds since it */
                                 /* takes an unsigned short anyway           */
    unsigned char     minutes;        /* 0 to 59                                  */
    unsigned char     hour;           /* 0 to 23                                  */
    unsigned char     dayOfWeek;      /* 1 to 7 (0 = not used, 1= Monday)         */
    unsigned char     dayOfMonth;     /* 1 to 28,29,30,31                         */
    unsigned char     month;          /* 1 to 12                                  */
    unsigned short int    year;           /* 1901 to 2099, the years over which the   */
                                 /* calculations in this module are valid    */
    bool   dstInEffect;    /* SD_TRUE when daylight savings time       */
                                 /* in effect, otherwise SD_FALSE            */
    bool   invalid;        /* set to SD_TRUE when the date/time        */
                                 /* is deemed inaccurate.  The level of      */
                                 /* inaccuracy is application-specific.      */
}UDD_TIME;


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

#endif // PCCLIENT_H
