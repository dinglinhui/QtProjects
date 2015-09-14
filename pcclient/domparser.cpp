#include <QtGui>
#include <QtXml>
//#include <iostream>

#include "domparser.h"

DomParser::DomParser(QTreeWidget *tree)
{
	treeWidget = tree;
}

bool DomParser::readFile(const QString &fileName)
{
	QFile file(fileName); //�����ļ���
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug("Error: Cannot read file " + qPrintable(fileName) + ": " + qPrintable(file.errorString()));
		//std::cerr << "Error: Cannot read file " << qPrintable(fileName) << ": " << qPrintable(file.errorString()) << std::endl;
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomDocument doc;
	if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
	{
		qDebug("Error: Parse error at line " + errorLine + ", column " + errorColumn + ": " + qPrintable(errorStr));
		//std::cerr << "Error: Parse error at line " << errorLine << ", " << "column " << errorColumn << ": " << qPrintable(errorStr) << std::endl;
		return false;
	}

	QDomElement root = doc.documentElement();
	if (root.tagName() != "bookindex")
	{
		qDebug("Error: Not a bookindex file");
		//std::cerr << "Error: Not a bookindex file" << std::endl;
		return false;
	}

	parseBookindexElement(root); //����ʵ�θ��β�
	return true;
}

void DomParser::parseBookindexElement(const QDomElement &element) //�β�������ʵ������һ��Ϊ��QDomElement &
{
	QDomNode child = element.firstChild(); //element��root���ݹ���
	while (!child.isNull())
	{
		//toElement()�����ǽ�����ΪQDomNode��childת��ΪQDomElement��Ȼ��child.toElement()�õ���tagName()
		if (child.toElement().tagName() == "entry")
			parseEntryElement(child.toElement(), treeWidget->invisibleRootItem()); //�ڶ���ʵ�Σ���
		child = child.nextSibling(); //��ǰ������һ�����
	}
}

void DomParser::parseEntryElement(const QDomElement &element, QTreeWidgetItem *parent)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(parent); //����ָ���������ʼ��
	item->setText(0, element.attribute("term")); //�����δ��ڱ�ǩ��

	QDomNode child = element.firstChild(); //elementΪһ��child��childΪ���ڵ�root���ӽڵ�
	while (!child.isNull())
	{
		if (child.toElement().tagName() == "entry")
		{
			parseEntryElement(child.toElement(), item); //ѭ������
		}
		else if (child.toElement().tagName() == "page")
		{
			parsePageElement(child.toElement(), item);
		}
		child = child.nextSibling();
	}
}

void DomParser::parsePageElement(const QDomElement &element, QTreeWidgetItem *parent)
{
	QString page = element.text(); //�����ڵ�
	QString allPages = parent->text(1);
	if (!allPages.isEmpty())
		allPages += ", ";
	allPages += page;
	parent->setText(1, allPages);
}
