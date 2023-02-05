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
};



#endif // MODELSTRUCT_HPP
