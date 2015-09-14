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
	QFile file(fileName); //传递文件名
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

	parseBookindexElement(root); //传递实参给形参
	return true;
}

void DomParser::parseBookindexElement(const QDomElement &element) //形参类型与实参类型一致为：QDomElement &
{
	QDomNode child = element.firstChild(); //element即root传递过来
	while (!child.isNull())
	{
		//toElement()作用是将类型为QDomNode的child转换为QDomElement，然后child.toElement()好调用tagName()
		if (child.toElement().tagName() == "entry")
			parseEntryElement(child.toElement(), treeWidget->invisibleRootItem()); //第二个实参？？
		child = child.nextSibling(); //当前结点的下一个结点
	}
}

void DomParser::parseEntryElement(const QDomElement &element, QTreeWidgetItem *parent)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(parent); //定义指针变量并初始化
	item->setText(0, element.attribute("term")); //给树形窗口标签名

	QDomNode child = element.firstChild(); //element为一级child；child为根节点root的子节点
	while (!child.isNull())
	{
		if (child.toElement().tagName() == "entry")
		{
			parseEntryElement(child.toElement(), item); //循环调用
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
	QString page = element.text(); //三级节点
	QString allPages = parent->text(1);
	if (!allPages.isEmpty())
		allPages += ", ";
	allPages += page;
	parent->setText(1, allPages);
}
