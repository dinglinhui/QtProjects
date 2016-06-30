#ifndef SQLTABLEMODEL_H_
#define SQLTABLEMODEL_H_

#include <QSqlTableModel>

class SqlTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    SqlTableModel();
    ~SqlTableModel();

protected:
    QVariant data( const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // SQLTABLEMODEL_H_
