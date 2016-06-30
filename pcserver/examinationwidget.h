#ifndef EXAMWIDGET_H
#define EXAMWIDGET_H

#include <QWidget>
#include "examinationtree.h"
#include "examinationtable.h"

class ExaminationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExaminationWidget(QWidget *parent = 0);
    ~ExaminationWidget();

signals:

public slots:
    void onTreeClicked(const QModelIndex &index);

private:
    ExaminationTree *examTree = nullptr;
    ExaminationTable *examTable = nullptr;
};

#endif // EXAMWIDGET_H
