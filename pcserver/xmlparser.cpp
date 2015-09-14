#include "xmlparser.h"
#include "utils.h"

XmlParser::XmlParser()
{
    if(!QFile::exists(PCSERVER_CONFIG_FILE))
    {
        createXml(PCSERVER_CONFIG_FILE);
    }

    localfile = new QFile(PCSERVER_CONFIG_FILE);
    if(!localfile->open(QFile::ReadWrite)){
        return;
    }

    dom = new QDomDocument();
    if(!dom->setContent(localfile)){
        localfile->close();
        return;
    }
}

XmlParser::~XmlParser()
{
    dom->clear();
    localfile->close();

    if(nullptr != localfile)
        delete localfile, localfile = nullptr;
    if(nullptr != dom)
        delete dom, dom = nullptr;
}

void XmlParser::createXml(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadWrite);

    QDomDocument doc;
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");

    QDomElement root = doc.createElement(XML_ELEMENT_CONFIGURATION);
    QDomElement element_root = doc.createElement(XML_ELEMENT_SERVER);

    QDomElement item_ipaddress = doc.createElement(XML_ELEMENT_ITEM);
    QDomAttr attr_key_ip = doc.createAttribute(XML_ELEMENT_KEY);
    QDomAttr attr_value_ip = doc.createAttribute(XML_ELEMENT_VALUE);
    attr_key_ip.setValue(XML_ELEMENT_IP_ADDRESS);
    attr_value_ip.setValue(XML_ELEMENT_IP_DEFAULT);
    item_ipaddress.setAttributeNode(attr_key_ip);
    item_ipaddress.setAttributeNode(attr_value_ip);

    QDomElement item_listenport = doc.createElement(XML_ELEMENT_ITEM);
    QDomAttr attr_key_port = doc.createAttribute(XML_ELEMENT_KEY);
    QDomAttr attr_value_port = doc.createAttribute(XML_ELEMENT_VALUE);
    attr_key_port.setValue(XML_ELEMENT_LISTEN_PORT);
    attr_value_port.setValue(XML_ELEMENT_PORT_DEFAULT);
    item_listenport.setAttributeNode(attr_key_port);
    item_listenport.setAttributeNode(attr_value_port);

    element_root.appendChild(item_ipaddress);
    element_root.appendChild(item_listenport);
    root.appendChild(element_root);
    doc.appendChild(instruction);
    doc.appendChild(root);

    QTextStream out(&file);
    doc.save(out,4);
    doc.clear();
    file.close();
}

void XmlParser::createXml(QString filename, void *context)
{
    if (context == nullptr)
    {
        qDebug() << "createXml context nullptr";
        createXml(filename);
        return;
    }
    SERVER_INFO *pServer = (SERVER_INFO *) context;

    QFile file(filename);
    file.open(QIODevice::ReadWrite);

    QDomDocument doc;
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");

    QDomElement root = doc.createElement(XML_ELEMENT_CONFIGURATION);
    QDomElement element_root = doc.createElement(XML_ELEMENT_SERVER);

    QDomElement item_ipaddress = doc.createElement(XML_ELEMENT_ITEM);
    QDomAttr attr_key_ip = doc.createAttribute(XML_ELEMENT_KEY);
    QDomAttr attr_value_ip = doc.createAttribute(XML_ELEMENT_VALUE);
    attr_key_ip.setValue(XML_ELEMENT_IP_ADDRESS);
    attr_value_ip.setValue(pServer->ipAddress);
    item_ipaddress.setAttributeNode(attr_key_ip);
    item_ipaddress.setAttributeNode(attr_value_ip);

    QDomElement item_listenport = doc.createElement(XML_ELEMENT_ITEM);
    QDomAttr attr_key_port = doc.createAttribute(XML_ELEMENT_KEY);
    QDomAttr attr_value_port = doc.createAttribute(XML_ELEMENT_VALUE);
    attr_key_port.setValue(XML_ELEMENT_LISTEN_PORT);
    attr_value_port.setValue(pServer->listenPort);
    item_listenport.setAttributeNode(attr_key_port);
    item_listenport.setAttributeNode(attr_value_port);

    element_root.appendChild(item_ipaddress);
    element_root.appendChild(item_listenport);
    root.appendChild(element_root);
    doc.appendChild(instruction);
    doc.appendChild(root);

    QTextStream out(&file);
    doc.save(out,4);
    doc.clear();
    file.close();
}


bool XmlParser::readXml(void *context, const QString &type)
{
    if (context == nullptr)
    {
        qDebug() << "readXml context nullptr";
        return false;
    }

    SERVER_INFO *pServer = (SERVER_INFO *) context;

    QDomNodeList nodelist = dom->elementsByTagName(type);
    if (nodelist.count() == 0)
    {
        qDebug() << type << " nodelist.count() == 0";
        return false;
    }

    for(int i=0; i<nodelist.count(); i++){
        QDomNode node = nodelist.at(i);
        QDomNodeList itemlist = node.childNodes();
        for(int j=0; j<itemlist.count(); j++){
            QDomNode mynode = itemlist.at(j);
            if(mynode.toElement().attribute(XML_ELEMENT_KEY) == XML_ELEMENT_IP_ADDRESS)
                pServer->ipAddress = mynode.toElement().attribute(XML_ELEMENT_VALUE);
            else if(mynode.toElement().attribute(XML_ELEMENT_KEY) == XML_ELEMENT_LISTEN_PORT)
                pServer->listenPort = mynode.toElement().attribute(XML_ELEMENT_VALUE);
        }
    }

    return true;
}

bool XmlParser::writeXml(void *context, const QString &type)
{
    QFile::remove(PCSERVER_CONFIG_FILE);
    createXml(PCSERVER_CONFIG_FILE, context);
    return true;
}

QString XmlParser::getValue(const QString &key, const QString &type)
{
    QString result = "";
    QDomNodeList nodelist = dom->elementsByTagName(type);
    for(int i=0; i<nodelist.count(); i++){
        QDomNode node = nodelist.at(i);
        QDomNodeList itemlist = node.childNodes();
        for(int j=0; j<itemlist.count(); j++){
            QDomNode mynode = itemlist.at(j);
            if(mynode.toElement().attribute(XML_ELEMENT_KEY) == key){
                result = mynode.toElement().attribute(XML_ELEMENT_VALUE);
                break;
            }
        }
    }

    if(result == "")
        qDebug() << QString("did't get value of %1, please check it.").arg(key);

    return result;
}
