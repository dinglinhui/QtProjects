#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <QtGui>
#include <QtXml>
#include <QFile>
#include <QDomDocument>
#include "pcdefs.h"
using namespace std;

class XmlParser: public QObject
{
    Q_OBJECT
public:
    XmlParser();
    virtual ~XmlParser();

public:
    void createXml(QString filename);
    void createXml(QString filename, void *context);
    bool readXml(void *context = nullptr, const QString &type = XML_ELEMENT_SERVER);
    bool writeXml(void *context = nullptr, const QString &type = XML_ELEMENT_SERVER);
    QString getValue(const QString &key, const QString &type = XML_ELEMENT_SERVER);

private:
    QFile *localfile = nullptr;
    QDomDocument *dom = nullptr;
};

#endif /* XMLPARSER_H_ */
