#ifndef SOCKETTHREAD_H_
#define SOCKETTHREAD_H_

#include <QStringList>
#include <QUdpSocket>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include "pcdefs.h"

class SocketThread: public QThread
{
Q_OBJECT

public:
	SocketThread(QObject *parent = 0);
	virtual ~SocketThread();
	//
	void initSocket();
	void closeSocket();
	void initServerInfo(SERVER_INFO *pServerInfo);
	//
	void stop();
	void sendToQueue(const QByteArray &buffer);

protected:
	void run();

private slots:
	void send(const QByteArray &buffer);
	void recv();
	void displayError(QAbstractSocket::SocketError socketError);

signals:
	void recvSignal(const QByteArray &buffer);

private:
	QUdpSocket *m_pUdpSocket;
	QHostAddress m_hIpTx;
	int m_nPortTx;
	int m_nPortRx;

	QQueue<QByteArray> m_sendQueue;
	QQueue<QByteArray> m_recvQueue;
	//
	bool m_bRunning;
	bool m_bStopped;
	bool m_bSocketInited;
};

#endif /* SOCKETTHREAD_H_ */
