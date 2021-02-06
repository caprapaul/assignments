#include "Model.h"

#include <vector>

using namespace std;

Model::Model(Service& service):
    service(service)
{
}

void Model::AddStar(std::string name, std::string constellation, int ra, int dec, int diameter)
{
    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(this->rowCount(), this->columnCount() - 1);

    this->service.AddStar(name, constellation, ra, dec, diameter);
    insertRows(this->service.GetAllStars().size() - 1, 1);
    //emit layoutChanged();
    emit dataChanged(topLeft, bottomRight, { Qt::DisplayRole, Qt::EditRole });
}

void Model::SaveSorted()
{
    this->service.SaveSorted();
}


bool Model::insertRows(int position, int rows, const QModelIndex& index)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);
    endInsertRows();
    return true;
}

int Model::rowCount(const QModelIndex & parent) const
{
    return service.GetAllStars().size();
}

QVariant Model::data(const QModelIndex & index, int role) const
{
    QVariant result = QVariant();

    int row = index.row();
    int column = index.column();

    if (!index.isValid() || row >= rowCount()) 
    {
        return result;
    }

    Domain domainData = service.GetAllStars()[row];
    vector<string> tokens = domainData.Serialize();

    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
        case 0:
            result = QString::fromStdString(tokens[0]);
            break;
        case 1:
            result = QString::fromStdString(tokens[1]);
            break;
        case 2:
            result = QString::fromStdString(tokens[2]);
            break;
        case 3:
            result = QString::fromStdString(tokens[3]);
            break;
        case 4:
            result = QString::fromStdString(tokens[4]);
            break;
        default:
            break;
        }
    }

    return result;
}

QVariant Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result = QVariant();

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
            case 0:
                result = QString("Name");
                break;
            case 1:
                result = QString("Constellation");
                break;
            case 2:
                result = QString("RA");
                break;
            case 3:
                result = QString("Dec");
                break;
            case 4:
                result = QString("Diameter");
                break;
            default:
                break;
            }
        }
    }

    return result;
}

int Model::columnCount(const QModelIndex& parent) const
{
    return 5;
}
