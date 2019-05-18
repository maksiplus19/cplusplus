#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H
#include <QAbstractItemModel>
#include <map>
#include <QVariant>

#include "qcustomplot.h"
#include "curveso.h"

class ProjectModel : public QAbstractItemModel
{
private:
    std::map<QString, CurveSO> map;
public:
    CurveSO get(QString) const;
    void add(CurveSO);

    ProjectModel(QObject* parent = nullptr);
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
};

#endif // PROJECTMODEL_H
