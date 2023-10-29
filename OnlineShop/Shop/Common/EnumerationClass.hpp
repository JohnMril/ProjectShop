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
//    ProductID,
//    ClientPriceListTypeID,

    ClientVendorCode,
    ClientBrandName,
    ClientProductName,
    ClientPriceString,
    ClientStorageMark,
    ClinentCurrencyType,
//    ClientProductID,
//    ClientPriceRecString,


    LAST_TYPE,
};


enum API : int
{
    LANIT,
    ASBIS,
    MARVEL,
    INLINE,
    RRC,
    PRONET,
    TRADEONLINE,
    OCS,
    NETLAB,
    MICS,
    ELKO,
    SUPERWAVE,
    RESOURCEMEDIA,
};

inline const QString  ConvertEnumToString(ElementsType type)
{
    switch (type)
    {

//    case ElementsType::ClientPriceListID: return "ClientPriceListID";
//    case ElementsType::ProductID: return "ProductID";
//    case ElementsType::ClientPriceListTypeID: return "ClientPriceListTypeID";
//    case ElementsType::ClientProductID: return "ClientProductID";
    case ElementsType::ClientVendorCode: return "Код вендора";
    case ElementsType::ClientBrandName: return "Наименования бренда";
    case ElementsType::ClientProductName: return "Наименование товара";
    case ElementsType::ClientPriceString: return "Цена";
//    case ElementsType::ClientPriceRecString: return "ClientPriceRecString";
    case ElementsType::ClientStorageMark: return "Кол-во на складе";
    case ElementsType::ClinentCurrencyType: return "Валюта";

    default: return  "";
    }
}






#endif // ENUMERATIONCLASS_HPP
