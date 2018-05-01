#include "SqlTableModel.h"

SqlTableModel::SqlTableModel() {
}

SqlTableModel::~SqlTableModel() {
}

QVariant SqlTableModel::data(const QModelIndex &item, int role) const {
    QVariant value = QSqlTableModel::data(item, role);

    if (role == Qt::TextAlignmentRole) {
        value = int(Qt::AlignHCenter | Qt::AlignVCenter);
        return value;
    }

    return value;
}

