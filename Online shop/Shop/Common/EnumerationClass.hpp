#ifndef ENUMERATIONCLASS_HPP
#define ENUMERATIONCLASS_HPP

#include <QString>
#include <QMap>

enum ElementsType
{
    DATE_TYPE,
    FLOAT_TYPE,
    INT_TYPE,
    VALUTA,
    TEXT,

    UNKNOWN_TYPE,
};


enum API : int
{
    LANIT,
    ASBIS,
};

inline const QString  ConvertEnumToString(ElementsType type)
{
    switch (type)
    {
    case ElementsType::DATE_TYPE: return "DATE_TYPE";
    case ElementsType::FLOAT_TYPE: return "FLOAT_TYPE";
    case ElementsType::INT_TYPE: return "INT_TYPE";
    case ElementsType::VALUTA: return "VALUTA";
    case ElementsType::TEXT: return "TEXT";

    default: return  "UNKNOWN_TYPE";
    }
}



#endif // ENUMERATIONCLASS_HPP
