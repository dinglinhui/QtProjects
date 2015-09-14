#ifndef ITEMDELEGATE_H_
#define ITEMDELEGATE_H_

#include <QtGui>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QItemDelegate>
#include "pcdefs.h"

class ReadOnlyDelegate: public QItemDelegate
{
Q_OBJECT
public:
	ReadOnlyDelegate(QObject *parent = 0) :
			QItemDelegate(parent)
	{
	}
	QWidget *createEditor(QWidget*parent, const QStyleOptionViewItem &option,
			const QModelIndex &index) const
	{
		return NULL;
	}
};

class UserIDDelegate: public QItemDelegate
{
Q_OBJECT
public:
	UserIDDelegate(QObject *parent = 0) :
			QItemDelegate(parent)
	{
	}
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
			const QModelIndex &index) const
	{
		QLineEdit *editor = new QLineEdit(parent);
		QRegExp regExp("[0-9]{0,10}");
		editor->setValidator(new QRegExpValidator(regExp, parent));
		return editor;
	}
	void setEditorData(QWidget *editor, const QModelIndex &index) const
	{
		QString text = index.model()->data(index, Qt::EditRole).toString();
		QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
		lineEdit->setText(text);
	}
	void setModelData(QWidget *editor, QAbstractItemModel *model,
			const QModelIndex &index) const
	{
		QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
		QString text = lineEdit->text();
		model->setData(index, text, Qt::EditRole);
	}
	void updateEditorGeometry(QWidget *editor,
			const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		editor->setGeometry(option.rect);
	}
};

class ValueDelegate: public QItemDelegate
{
Q_OBJECT
public:
	ValueDelegate(QObject *parent = 0) :
			QItemDelegate(parent)
	{
	}
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
			const QModelIndex &index) const
	{
		QLineEdit *editor = new QLineEdit(parent);
//		QRegExp regExp("^[0-9]+(.[0-9]{1,4})?$");
		QRegExp regExp("^(-?\\d+)(\\.\\d+)?$");
		editor->setValidator(new QRegExpValidator(regExp, parent));
		return editor;
	}
	void setEditorData(QWidget *editor, const QModelIndex &index) const
	{
		QString text = index.model()->data(index, Qt::EditRole).toString();
		QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
		lineEdit->setText(text);
	}
	void setModelData(QWidget *editor, QAbstractItemModel *model,
			const QModelIndex &index) const
	{
		QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
		QString text = lineEdit->text();
		model->setData(index, text, Qt::EditRole);
	}
	void updateEditorGeometry(QWidget *editor,
			const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		editor->setGeometry(option.rect);
	}
};

class AgeDelegate: public QItemDelegate
{
Q_OBJECT
public:
	AgeDelegate(QObject *parent = 0) :
			QItemDelegate(parent)
	{
	}
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
			const QModelIndex &index) const
	{
		QSpinBox *editor = new QSpinBox(parent);
		editor->setMinimum(1);
		editor->setMaximum(100);
		return editor;
	}
	void setEditorData(QWidget *editor, const QModelIndex &index) const
	{
		int value = index.model()->data(index, Qt::EditRole).toInt();
		QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
		spinBox->setValue(value);
	}
	void setModelData(QWidget *editor, QAbstractItemModel *model,
			const QModelIndex &index) const
	{
		QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
		spinBox->interpretText();
		int value = spinBox->value();
		model->setData(index, value, Qt::EditRole);
	}
	void updateEditorGeometry(QWidget *editor,
			const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		editor->setGeometry(option.rect);
	}
};


class SexDelegate: public QItemDelegate
{
Q_OBJECT
public:
	SexDelegate(QObject *parent = 0) :
			QItemDelegate(parent)
	{
	}
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
			const QModelIndex &index) const
	{
		QComboBox *editor = new QComboBox(parent);
		editor->addItem("Female");
		editor->addItem("Male");
		return editor;
	}
	void setEditorData(QWidget *editor, const QModelIndex &index) const
	{
		QString text = index.model()->data(index, Qt::EditRole).toString();
		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		int tindex = comboBox->findText(text);
		comboBox->setCurrentIndex(tindex);
	}
	void setModelData(QWidget *editor, QAbstractItemModel *model,
			const QModelIndex &index) const
	{
		QComboBox *comboBox = static_cast<QComboBox*>(editor);
		QString text = comboBox->currentText();
		model->setData(index, text, Qt::EditRole);
	}
	void updateEditorGeometry(QWidget *editor,
			const QStyleOptionViewItem &option, const QModelIndex &index) const
	{
		editor->setGeometry(option.rect);
	}
};


#endif /* RTDBITEMDELEGATE_H_ */
