#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include <QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

#include "Common/ModelStruct.hpp"
#include "DataClass/DataClass.hpp"

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

    QMap<QString, QStandardItemModel *> GetMapModelsRaw() const;

    QMap<QString, QSortFilterProxyModel *> GetMapOfProxyModels() const;

    void SetDataClass(DataClass *dataClass);

    QSortFilterProxyModel * GetLastProxyModel() const;


    void CreateModel_1(const ModelStruct& modelStruct);

    QModelIndex GetIndexOfPlacesModelByName(QString shopName);

signals:
    void CreatedNewModel(const QString&);

public slots:

    void CreateModelByString( QString modelName);


private:


    QStandardItemModel* m_placesModels;

    QStandardItemModel* m_tmpModel;


    QMap<QString, QStandardItemModel*> m_mapModels;

    QMap<QString, QSortFilterProxyModel*> m_mapOfProxy;


    DataClass* m_dataClass;
};




#endif // MODELHANDLER_HPP