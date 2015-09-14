#include "transmitthread.h"

TransmitThread::TransmitThread(QObject *parent) :
    QThread(parent),
    m_pTcpSocket(NULL),
    m_hHostIp(QHostAddress("127.0.0.1")),
    m_nHostPort(6010),
    m_bConnect(false),
    m_bDisconnect(false),
    m_bRunning(false),
    m_bStopped(false)
{
    connect(this, SIGNAL(recvSignal(const QByteArray &)), parent, SLOT(switchStation(const QByteArray &)));
    connect(this, SIGNAL(connectSignal()), parent, SLOT(connectRequest()));
    connect(this, SIGNAL(disconnectSignal()), parent, SLOT(disconnectRequest()));
}

TransmitThread::~TransmitThread()
{

}

void TransmitThread::run()
{
    m_bRunning = true;
    m_pTcpSocket = new QTcpSocket;
    initSocket();

    forever
    {
        if(m_bStopped)
        {
            closeSocket();
            //mutex.lock();
            m_recvQueue.clear();
            m_sendQueue.clear();
            //mutex.unlock();
            break;
        }

        if(m_pTcpSocket->state() == QAbstractSocket::ConnectedState)
        {
            m_pTcpSocket->waitForDisconnected(10);
            m_pTcpSocket->waitForReadyRead(10);

            if(m_bDisconnect)
            {
                closeSocket();
                m_bDisconnect = false;
            }
            else
            {
                emit disconnectSignal();
            }
        }
        else
        {
            if(m_bConnect)
            {
                m_pTcpSocket->connectToHost(m_hHostIp, m_nHostPort);
                m_pTcpSocket->waitForConnected(1000);
                m_bConnect = false;
            }
            else
            {
                emit connectSignal();
            }
        }

        //mutex.lock();
        if (!m_recvQueue.isEmpty())
        {
            emit recvSignal(m_recvQueue.dequeue());
        }

        if (!m_sendQueue.isEmpty())
        {
            send(m_sendQueue.dequeue());
        }

        if (m_recvQueue.isEmpty() && m_sendQueue.isEmpty())
        {
            msleep(50);
        }
        //mutex.unlock();
    }

    if (m_pTcpSocket != NULL)
    {
        delete m_pTcpSocket, m_pTcpSocket = NULL;
    }
    this->exec();
}

void TransmitThread::stop()
{
    m_bStopped = true;
}

void TransmitThread::connectSocket()
{
    m_bConnect = true;
    m_bDisconnect = false;
}

void TransmitThread::disconnectSocket()
{
    m_bConnect = false;
    m_bDisconnect = true;
}

void TransmitThread::closeSocket()
{
    if(m_pTcpSocket->state() == QAbstractSocket::ConnectedState)
        m_pTcpSocket->disconnectFromHost();

    if(m_pTcpSocket->state() != QAbstractSocket::UnconnectedState)
        m_pTcpSocket->waitForDisconnected(-1);

    m_pTcpSocket->abort();
    m_pTcpSocket->close();
}

void TransmitThread::initSocket()
{
    connect(m_pTcpSocket, SIGNAL(readyRead()), this, SLOT(recv()), Qt::DirectConnection);
}

void TransmitThread::initServerInfo(SERVER_INFO *pServerInfo)
{
    m_hHostIp = QHostAddress(pServerInfo->ip);
    m_nHostPort = pServerInfo->transPort.toInt();
}

void TransmitThread::displayError(QAbstractSocket::SocketError socketError)
{
    qDebug() << m_pTcpSocket->errorString() << socketError;
}

void TransmitThread::send(const QByteArray &buffer)
{
    if (!m_bRunning)
        return;

    //qDebug() << buffer.toHex() << buffer.size();
    m_pTcpSocket->write(buffer, buffer.size());
}

void TransmitThread::sendToQueue(const QByteArray &buffer)
{
    //mutex.lock();
    m_sendQueue.enqueue(buffer);
    //mutex.unlock();
}

void TransmitThread::recv()
{
    if (!m_bRunning)
        return;

    QByteArray datagram = m_pTcpSocket->readAll();
    if (datagram.size() > 0)
    {
        //mutex.lock();
        m_recvQueue.enqueue(datagram);
        //mutex.unlock();
    }
//    qDebug() << datagram.toHex() << datagram.size();
}
