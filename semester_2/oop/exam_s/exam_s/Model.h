#pragma once

#include "Service.h"
#include <QAbstractTableModel>

class Model : public QAbstractTableModel
{
private:
    Service& service;

public:
    Model(Service& service);

    // Adds a star to the list.
    // Throws a ServiceException if name already exists, name is empty or diameter is not greater than 0.
    void AddStar(std::string name, std::string constellation, int ra, int dec, int diameter);
    void SaveSorted();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool Model::insertRows(int position, int rows, const QModelIndex& index = QModelIndex()) override;
};

