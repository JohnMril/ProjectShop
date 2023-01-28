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

    void CreateModel(ModelStruct modelStruct);

    QStandardItemModel* GetPlacesModels() const;

    QStandardItemModel* GetMainShop() const;

    void RemoveRows(int row);

private:

    QStandardItemModel* m_placesModels;

    QStandardItemModel* m_mainShop;

    QVector<QStandardItemModel*> m_vecModels;

    QVector<ModelStruct> m_vecRawData;
};

#endif // MODELHANDLER_HPP
