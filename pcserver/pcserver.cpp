#include "pcserver.h"

PCServer::PCServer() :
    m_pServer(new TcpServer(this))
{
    m_pServer->listen(QHostAddress::Any, 16011);
    connect(m_pServer,&TcpServer::connectClient,this,&PCServer::sockConnect);//连接信号
    connect(m_pServer,&TcpServer::sockDisConnect,this,&PCServer::sockDisConnect);//断开信号
}

PCServer::~PCServer()
{

}

void PCServer::sockConnect(const int socketDescriptor, const QString & ip,const quint16 port)
{
    qDebug() << "socket connect" << socketDescriptor << " " << ip << " " << port << endl;
}

void PCServer::sockDisConnect(const int socketDescriptor, const QString & ip,const quint16 port)
{
    qDebug() << "socket disconnect" << socketDescriptor << " " << ip << " " << port << endl;
}

void PCServer::run()
{
    //    qDebug() << "pcserver starting" << endl;
    m_bRunning = true;
    forever
    {
        if (m_bStopped)
        {
            m_bStopped = false;
            //mutex.lock();
            m_recvQueue.clear();
            m_sendQueue.clear();
            //mutex.unlock();
            break;
        }

        // mutex.lock();
        if (!m_recvQueue.isEmpty())
        {
            //            emit recvSignal(m_recvQueue.dequeue());
        }

        if (!m_sendQueue.isEmpty())
        {
            //            send(m_sendQueue.dequeue());
        }

        if(m_recvQueue.isEmpty()&&m_sendQueue.isEmpty())
        {
            msleep(50);
        }
        //mutex.unlock()
    }

    this->exec();
}

void PCServer::setListenProperty(const QHostAddress &address, quint16 port)
{
    m_pServer->listen(address, port);
}
