#ifndef MODELSTRUCT_HPP
#define MODELSTRUCT_HPP

#include <QVector>
#include <QVariant>
#include <QPair>
#include <QVariantMap>
#include <QMap>

#include "EnumerationClass.hpp"


struct ModelStruct
{
    QVector<QVariantMap> modelMap;
    QString date;
    QString shop;

    friend bool operator==(const ModelStruct& model0, const ModelStruct& model1)
    {
        return (model0.shop == model1.shop);
    }
};



struct ElementSettings
{
    bool enabled = false;
    int number;
    QString keyName;
    QString valueName;
    ElementsType type;
};



struct ModelSettings
{
    QString shop;
    QMap<QString, ElementSettings> mapSettings;

    friend bool operator==(const ModelSettings& model0, const ModelSettings& model1)
    {
        return (model0.shop == model1.shop);
    }
};



#endif // MODELSTRUCT_HPP
