#ifndef TRANSMITTHREAD_H
#define TRANSMITTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include <QQueue>
#include <QMutex>
#include "pcdefs.h"

class TransmitThread : public QThread
{
    Q_OBJECT

public:
    TransmitThread(QObject *parent = 0);
    virtual ~TransmitThread();
    //
    void connectSocket();
    void disconnectSocket();
    void closeSocket();
    void initSocket();
    void initServerInfo(SERVER_INFO *pServerInfo);
    void stop();
    //
    void sendToQueue(const QByteArray &buffer);

protected:
    virtual void run();

private slots:
    void send(const QByteArray &buffer);
    void recv();
    void displayError(QAbstractSocket::SocketError socketError);

signals:
    void recvSignal(const QByteArray &buffer);
    void connectSignal();
    void disconnectSignal();

private:
    QTcpSocket *m_pTcpSocket;
    //QMutex mutex;
    QQueue<QByteArray> m_sendQueue;
    QQueue<QByteArray> m_recvQueue;
    //
    QHostAddress m_hHostIp;
    int m_nHostPort;
    //
    bool m_bConnect;
    bool m_bDisconnect;
    //
    bool m_bRunning;
    bool m_bStopped;
};

#endif // TRANSMITTHREAD_H
