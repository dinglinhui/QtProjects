#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <QtGui>
#include <QtXml>
#include "pcdefs.h"
using namespace std;

class XmlParser: public QObject
{
    Q_OBJECT
public:
    XmlParser();
    virtual ~XmlParser();

public:
    bool readXml(const QString &fileName, const QString tag, void *context);
    bool writeXml(const QString &fileName, const QString tag, void *context);

private:
    QMutex m_hLock;
};

#endif /* XMLPARSER_H_ */
