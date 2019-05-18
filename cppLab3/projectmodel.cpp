#include "projectmodel.h"

CurveSO ProjectModel::get(QString s) const
{
    return map.at(s);
}

void ProjectModel::add(CurveSO curve)
{
    map.insert(std::pair<QString, CurveSO>(curve.get_name(), curve));
    QString();
}

ProjectModel::ProjectModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QModelIndex ProjectModel::index(int row, int column, const QModelIndex &parent) const
{
    return createIndex(row, column);
}

QModelIndex ProjectModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QVariant ProjectModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return index.data().toString();
        break;
    case Curve::CurveRole:
        return QVariant::fromValue(map.at(index.data().toString()));
    default:
        break;
    }
}

int ProjectModel::rowCount(const QModelIndex &parent) const
{
    return map.size();
}

int ProjectModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}
