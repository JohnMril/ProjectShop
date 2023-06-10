#include "SqlDataBase.hpp"

SqlDataBase::SqlDataBase(QObject *parent) : QObject(parent)
{

}



bool SqlDataBase::MakeConection(QString serverAdres, QString dataBaseName, QString userName, QString password)
{

    m_dataBase = QSqlDatabase::addDatabase("QODBC");

    m_dataBase.setDatabaseName("DRIVER={SQL Server};SERVER="+serverAdres+";DATABASE="+dataBaseName+";");
    m_dataBase.setUserName(userName);
    m_dataBase.setPassword(password);

    if(m_dataBase.open())
    {
        qDebug() <<" SQL connection SUCCESS";
        return true;
    }

    qDebug() <<" SQL connection ERROR";
    return false;

}



void SqlDataBase::InsertItems(QVector<QVariantList> itemList)
{
    QSqlQuery query;
    query.prepare("INSERT INTO PRICE_LIST_TMP ( ClientPriceListID, ProductID, ClientPriceListTypeID, ClientProductID, ClientVendorCode, ClientBrandName, ClientProductName, ClientPriceString, ClientPriceRecString, ClientStorageMark)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");

    for (auto item  : itemList)
    {
        for (auto property : item)
        {
            query.addBindValue(property.toInt());
        }
        if(!query.exec())
        {
            qDebug() <<"Error "<< query.lastError();
        }
    }
}
