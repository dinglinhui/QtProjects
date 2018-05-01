#ifndef COMBOBOXITEM_H
#define COMBOBOXITEM_H

#include <QLabel>
#include <QHBoxLayout>

class ComboboxItem : public QWidget
{
    Q_OBJECT
public:
    explicit ComboboxItem(QWidget *parent = nullptr);
    virtual ~ComboboxItem();

    void setLabelContent(const QString& content);

signals:

public slots:

private:
    QLabel* m_img, *m_label;
    QHBoxLayout* m_layout;
};

#endif // COMBOBOXITEM_H
