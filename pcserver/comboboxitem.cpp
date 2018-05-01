#include "comboboxitem.h"

ComboboxItem::ComboboxItem(QWidget *parent)
    : QWidget(parent)
{
    m_img = new QLabel(this);
    QPixmap pic(QStringLiteral(":/res/images/"));
    m_img->setPixmap(pic);
    m_img->setFixedSize(pic.size());
    m_label = new QLabel(this);

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_label);
    m_layout->addStretch();
    m_layout->addWidget(m_img);

    m_layout->setSpacing(5);
    m_layout->setContentsMargins(5, 5, 5, 5);

    setLayout(m_layout);
}

ComboboxItem::~ComboboxItem()
{

}

void ComboboxItem::setLabelContent(const QString& content)
{
    m_label->setText(content);
}
