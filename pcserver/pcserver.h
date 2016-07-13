#ifndef PCSERVER_H
#define PCSERVER_H

#include <QQueue>
#include <QByteArray>
#include <QThread>
#include <QDebug>
#include "tcpserver.h"

class PCServer: public QThread {
    Q_OBJECT
public:
    explicit PCServer();
    ~PCServer();

public slots:
    void sockConnect(const int socketDescriptor, const QString & ip,const quint16 port);
    void sockDisConnect(const int socketDescriptor, const QString & ip,const quint16 port);

protected:
    virtual void run();

    void setListenProperty(const QHostAddress &address = QHostAddress::Any, quint16 port = 16011);

private:
    //
    TcpServer *m_pServer;
    //
    QQueue<QByteArray> m_sendQueue;
    QQueue<QByteArray> m_recvQueue;
    //
    bool m_bRunning;
    bool m_bStopped;
    bool m_bSocketInited;
};

#endif // PCSERVER_H
