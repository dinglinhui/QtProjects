
void Network::run()
{
    if(socket == 0)
    {
        socket = new QTcpSocket;
        connect(socket,SIGNAL(readyRead()),this,SLOT(readS ocket()), Qt:DirectConnection);
        connect(socket,SIGNAL(error(QAbstractSocket::Socke tError)),this,SLOT(displayError(QAbstractSocket::SocketError)),
                Qt:DirectConnection);

    }

    if(socket->state() == QAbstractSocket::ConnectedState)
        socket->disconnectFromHost();
    if(socket->state() != QAbstractSocket::UnconnectedState)
        socket->waitForDisconnected(-1);

    socket->connectToHost(ip,port);
    stopConnect = false;

    while(!socket->waitForConnected(3000))
    {
        if(stopConnect)
        {
            return;
        }
        qDebug()<<socket->state()<<socket->error()<<socket->errorString();
    }

    exec();
}

void Network::setAddress(QString ip_,qint16 port_)
{
    ip = ip_;
    port = port_;

    stopConnect = true;//TODO-Eliminate this bool from program
    if(isRunning())
    {
        quit();
        wait();
    }
    start();
}

void Network::write2socket(QString str)
{
    if( (socket == 0) || (!socket->isWritable()) )
        return;
    socket->write(str.toAscii());
    socket->flush();
}
