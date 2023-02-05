#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include <QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

#include "Common/ModelStruct.hpp"

class ModelHandler : public QObject
{
    Q_OBJECT
public:
    explicit ModelHandler(QObject *parent = nullptr);

    void CreateModel(const ModelStruct &modelStruct);

    void AppendRowToPlacesModel(QVariant name, QVariant data);

    void CreateModels( QVector<ModelStruct>& modelsStructVec);

    QStandardItemModel* GetPlacesModels() const;

    QStandardItemModel* GetMainShop() const;

    void RemoveRows(int row);

    QMultiMap<QString, QStandardItemModel *> GetMapModelsRaw() const;

    QMultiMap<QString, QSortFilterProxyModel *> GetMapOfProxyModels() const;

signals:
    void CreatedNewModel();

private:

    QVector<ModelStruct> m_modelsStructVec;

    QStandardItemModel* m_placesModels;

    QStandardItemModel* m_tmpModel;


    QMultiMap<QString, QStandardItemModel*> m_mapModels;

    QMultiMap<QString, QSortFilterProxyModel*> m_mapOfProxy;

    QVector<ModelStruct> m_vecRawData;
};

#endif // MODELHANDLER_HPP
