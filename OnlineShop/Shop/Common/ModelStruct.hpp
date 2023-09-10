#ifndef MODELSTRUCT_HPP
#define MODELSTRUCT_HPP

#include <QVector>
#include <QVariant>
#include <QPair>
#include <QVariantMap>
#include <QMap>
#include <QSet>

#include "Common/EnumerationClass.hpp"


struct ModelStruct
{
    QVector<QVariantMap> modelMap;
    QString date;
    QString shop;
    QSet<QString> setAttributs;

    friend bool operator==(const ModelStruct& model0, const ModelStruct& model1)
    {
        return ((model0.shop == model1.shop)&&(model0.date==model1.date));
    }

    uint columnCount() const
    {
        return setAttributs.size();
    }

    uint rowCount() const
    {
        return modelMap.size();
    }
};



struct ElementSettings
{
    bool enabled = false;
    int number;
    QString keyName;
    QString valueName;
    ElementsType type;
    friend bool operator==(const ElementSettings& model0, const ElementSettings& model1)
    {
        return (model0.keyName == model1.keyName) && (model0.type == model1.type);
    }
};



struct ModelSettings
{
    QString shop;
    QString date;
    bool    isSuccess = false;
    //TODO убрать потом в файл настроек
    int clientPriceListID;
    QMap<QString, ElementSettings> mapSettings;

    QMap<ElementsType, QString> elementTypeMap;

    friend bool operator==(const ModelSettings& model0, const ModelSettings& model1)
    {
        return (model0.elementTypeMap == model1.elementTypeMap);
    }
};



#endif // MODELSTRUCT_HPP
