#ifndef ENUMERATIONCLASS_HPP
#define ENUMERATIONCLASS_HPP

#include <QString>
#include <QMap>

enum ElementsType : int
{

    /*    ClientPriceListID int,
    ProductID int,
    ClientPriceListTypeID int,
    ClientProductID varchar(500),
    ClientVendorCode varchar(2000),
    ClientBrandName varchar(500),
    ClientProductName varchar(2000),
    ClientPriceString varchar(200),
    ClientPriceRecString varchar(200),
    ClientStorageMark varchar(500)
    */
   // ClientPriceListID,
    ProductID,
//    ClientPriceListTypeID,
//    ClientProductID,
    ClientVendorCode,
    ClientBrandName,
    ClientProductName,
    ClientPriceString,
//    ClientPriceRecString,
    ClientStorageMark,


    NOTHING,
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

//    case ElementsType::ClientPriceListID: return "ClientPriceListID";
    case ElementsType::ProductID: return "ProductID";
//    case ElementsType::ClientPriceListTypeID: return "ClientPriceListTypeID";
//    case ElementsType::ClientProductID: return "ClientProductID";
    case ElementsType::ClientVendorCode: return "ClientVendorCode";
    case ElementsType::ClientBrandName: return "ClientBrandName";
    case ElementsType::ClientProductName: return "ClientProductName";
    case ElementsType::ClientPriceString: return "ClientPriceString";
//    case ElementsType::ClientPriceRecString: return "ClientPriceRecString";
    case ElementsType::ClientStorageMark: return "ClientStorageMark";

    default: return  "";
    }
}






#endif // ENUMERATIONCLASS_HPP
