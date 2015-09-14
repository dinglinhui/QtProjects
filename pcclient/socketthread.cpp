#include <QtGui>
#include <QtNetwork>
#include "socketthread.h"

SocketThread::SocketThread(QObject *parent) :
		QThread(parent)
{
	m_pUdpSocket = new QUdpSocket(this);
	m_hIpTx = QHostAddress("127.0.0.1");
	m_nPortTx = 6008;
	m_nPortRx = 6009;
	m_bRunning = false;
	m_bStopped = false;
	m_bSocketInited = false;
	connect(this, SIGNAL(recvSignal(const QByteArray &)), parent, SLOT(switchStation(const QByteArray &)));
}

SocketThread::~SocketThread()
{
	delete m_pUdpSocket;
}

void SocketThread::run()
{
	m_bRunning = true;
	forever
	{
		if (m_bStopped)
		{
			m_bStopped = false;
			break;
		}

		if (!m_recvQueue.isEmpty())
		{
			emit recvSignal(m_recvQueue.dequeue());
		}

		if (!m_sendQueue.isEmpty())
		{
			send(m_sendQueue.dequeue());
		}

		if(m_recvQueue.isEmpty()&&m_sendQueue.isEmpty())
		{
			msleep(50);
		}
	}

	this->exec();
}

void SocketThread::stop()
{
	closeSocket();
	m_bStopped = true;
}

void SocketThread::initSocket()
{
	if (!m_bSocketInited)
	{
		m_pUdpSocket->bind(QHostAddress::Any, m_nPortRx);
		connect(m_pUdpSocket, SIGNAL(readyRead()), this, SLOT(recv()));
		m_bSocketInited = true;
	}
}

void SocketThread::closeSocket()
{
	if (m_bSocketInited)
	{
		m_pUdpSocket->close();
		m_bSocketInited = false;
	}
}

void SocketThread::initServerInfo(SERVER_INFO *pServerInfo)
{
	m_hIpTx = QHostAddress(pServerInfo->ip);
	m_nPortRx = pServerInfo->srcPort.toInt();
	m_nPortTx = pServerInfo->destPort.toInt();

	initSocket();
}

void SocketThread::displayError(QAbstractSocket::SocketError socketError)
{
	qDebug() << m_pUdpSocket->errorString();
}

void SocketThread::send(const QByteArray &buffer)
{
	if(!m_bRunning)
		return;

	//qDebug() << buffer.toHex() << buffer.size();
	m_pUdpSocket->writeDatagram(buffer, buffer.size(), m_hIpTx, m_nPortTx);
}

void SocketThread::sendToQueue(const QByteArray &buffer)
{
	m_sendQueue.enqueue(buffer);
}

void SocketThread::recv()
{
	if(!m_bRunning)
		return;

	while (m_pUdpSocket->hasPendingDatagrams())
	{
		QByteArray datagram;
		datagram.resize(m_pUdpSocket->pendingDatagramSize());
		m_pUdpSocket->readDatagram(datagram.data(), datagram.size());

		m_recvQueue.enqueue(datagram);
		//qDebug() << datagram.toHex() << datagram.size();
	}
}
