#ifndef TRANSMITTABLE_H
#define TRANSMITTABLE_H

#include <QTableView>
#include "proxymodel.h"
#include "pcdefs.h"

class TransmitTable : public QTableView
{
    Q_OBJECT
public:
    explicit TransmitTable(QWidget *parent = 0);
    ~TransmitTable();
};

#endif // TRANSMITTABLE_H
