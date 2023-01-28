#ifndef MODELSTRUCT_HPP
#define MODELSTRUCT_HPP

#include <QVector>
#include <QVariant>
#include <QPair>
#include <QVariantMap>


struct ModelStruct
{
    QVector<QVariantMap> modelMap;
    QString data;
    QString shop;
};

#endif // MODELSTRUCT_HPP
