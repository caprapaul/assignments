#include "SavedMaterialsModel.h"

SavedMaterialsModel::SavedMaterialsModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int SavedMaterialsModel::rowCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

int SavedMaterialsModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}

QVariant SavedMaterialsModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return QString("Row%1, Column%2")
        .arg(index.row() + 1)
        .arg(index.column() + 1);

    return QVariant();
}
