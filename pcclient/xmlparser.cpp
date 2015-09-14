#include "xmlparser.h"

XmlParser::XmlParser()
{
}

XmlParser::~XmlParser()
{
}

bool XmlParser::readXml(const QString &fileName, const QString tag, void *context)
{
    if (context == NULL)
        return false;

    m_hLock.lock();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open file!" << fileName;
        m_hLock.unlock();
        return false;
    }

    QDomDocument doc;
    doc.clear();
    if (!doc.setContent(&file))
    {
        qDebug() << "doc.setContent fail!";
        m_hLock.unlock();
        file.close();
        return false;
    }
    file.close();

    QDomElement rootElem = doc.documentElement();
    QDomNode rootNode = rootElem.firstChild();
    while (!rootNode.isNull())
    {
        QDomElement firElem = rootNode.toElement();
        if (!firElem.isNull())
        {
            if (tag == firElem.tagName())
            {
                qDebug() << firElem.tagName();
                if (tag == XML_ELEMENT_SERVERINFO)
                {
                    SERVER_INFO *pServer = (SERVER_INFO *) context;

                    QDomNode firNode = firElem.firstChild();
                    while (!firNode.isNull())
                    {
                        QDomElement secElem = firNode.toElement();
                        if (!secElem.isNull())
                        {
                            qDebug() << secElem.tagName() << ":" << secElem.text();
                            if (secElem.tagName() == XML_ELEMENT_IP)
                            {
                                pServer->ip = secElem.text();
                            }
                            else if (secElem.tagName() == XML_ELEMENT_SRCPORT)
                            {
                                pServer->srcPort = secElem.text();
                            }
                            else if (secElem.tagName() == XML_ELEMENT_DESTPORT)
                            {
                                pServer->destPort = secElem.text();
                            }
                            else if (secElem.tagName() == XML_ELEMENT_TRANSPORT)
                            {
                                pServer->transPort = secElem.text();
                            }
                            else if (secElem.tagName() == XML_ELEMENT_TRANSENABLE)
                            {
                                pServer->transEnable = secElem.text();
                            }

                        }
                        firNode = firNode.nextSibling();
                    }

                }
                else
                {
                    qDebug() << "XML " << fileName << " Error !";
                }
            }
        }
        rootNode = rootNode.nextSibling();
    }
    doc.clear();
    m_hLock.unlock();
    return true;
}

bool XmlParser::writeXml(const QString &fileName, const QString tag, void *context)
{
    if (context == NULL)
    {
        qDebug() << "context NULL";
        return false;
    }

    m_hLock.lock();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Can't open file!" << fileName;
        m_hLock.unlock();
        return false;
    }
    QDomDocument doc;
    doc.clear();
    if (!doc.setContent(&file))
    {
        qDebug() << "doc.setContent fail!";
        m_hLock.unlock();
        file.close();
        return false;
    }
    file.close();

    QDomElement rootElem = doc.documentElement();
    QDomNode rootNode = rootElem.firstChild();
    while (!rootNode.isNull())
    {
        QDomElement firElem = rootNode.toElement();
        if (!firElem.isNull())
        {
            if (tag == firElem.tagName())
            {
                if (tag == XML_ELEMENT_SERVERINFO)
                {
                    SERVER_INFO *pServer = (SERVER_INFO *) context;
                    QDomNode oldNode = firElem.firstChild();
                    QDomNode firNode = firElem.firstChild();
                    while (!firNode.isNull())
                    {
                        QDomElement secElem = firNode.toElement();
                        if (!secElem.isNull())
                        {
                            QDomNode secNode = secElem.firstChild();
                            if (secElem.tagName() == XML_ELEMENT_IP)
                            {
                                secNode.setNodeValue(pServer->ip);
                            }
                            else if (secElem.tagName() == XML_ELEMENT_SRCPORT)
                            {
                                secNode.setNodeValue(pServer->srcPort);
                            }
                            else if (secElem.tagName() == XML_ELEMENT_DESTPORT)
                            {
                                secNode.setNodeValue(pServer->destPort);
                            }
                            else if (secElem.tagName() == XML_ELEMENT_TRANSPORT)
                            {
                                secNode.setNodeValue(pServer->transPort);
                            }
                            else if (secElem.tagName() == XML_ELEMENT_TRANSENABLE)
                            {
                                secNode.setNodeValue(pServer->transEnable);
                            }
                        }
                        firNode = firNode.nextSibling();
                    }
                    QDomNode newNode = firElem.firstChild();

                    //qDebug() << newNode.toElement().text() << oldNode.toElement().text();
                    firElem.replaceChild(newNode, oldNode);
                }
                else
                {
                    qDebug() << "XML " << fileName << " Error !";
                }
            }
        }
        rootNode = rootNode.nextSibling();
    }

    QFile fileNew(fileName);
    if (!fileNew.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Can't update file!";
        return false;
    }

    QTextStream out(&fileNew);
    out << doc.toString();
//    doc.save(out);

    doc.clear();
    fileNew.close();
    m_hLock.unlock();

    return true;
}

