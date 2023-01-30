#ifndef MODELHANDLER_HPP
#define MODELHANDLER_HPP

#include <QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>

#include "ModelStruct.hpp"

class ModelHandler : public QObject
{
    Q_OBJECT
public:
    explicit ModelHandler(QObject *parent = nullptr);

    void CreateModel( ModelStruct &modelStruct);

    void CreateModels( QVector<ModelStruct>& modelsStructVec);

    QStandardItemModel* GetPlacesModels() const;

    QStandardItemModel* GetMainShop() const;

    void RemoveRows(int row);

private:

    QVector<ModelStruct> m_modelsStructVec;

    QStandardItemModel* m_placesModels;

    QStandardItemModel* m_tmpModel;

    QMap<QString, QStandardItemModel*> m_mapModels;

    QVector<ModelStruct> m_vecRawData;
};

#endif // MODELHANDLER_HPP
