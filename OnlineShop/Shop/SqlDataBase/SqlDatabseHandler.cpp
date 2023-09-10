#include "SqlDatabseHandler.hpp"

SqlDatabaseHandler::SqlDatabaseHandler(DataClass *dataClass, QWidget *parent) :
    QWidget(parent),
    m_dataClass(dataClass)
{

}

bool SqlDatabaseHandler::isConnected() const
{
    return m_isConnected;
}

bool SqlDatabaseHandler::MakeConection(QString serverAdres, QString dataBaseName, QString userName, QString password)
{
    m_dataBase = QSqlDatabase::addDatabase("QODBC");

    m_dataBase.setDatabaseName("DRIVER={SQL Server};SERVER="+serverAdres+";DATABASE="+dataBaseName+";");
    m_dataBase.setUserName(userName);
    m_dataBase.setPassword(password);

    if(m_dataBase.open())
    {
        qDebug() <<" SQL connection SUCCESS";
        m_isConnected = true;
        return true;
    }

    qDebug() <<" SQL connection ERROR";
    m_isConnected = false;
    return false;
}



void SqlDatabaseHandler::PrepareToSend(QString shopName)
{
    if(!m_isConnected)
    {
        emit NeedToConnect();
        return;
    }

    if(m_dataClass->IsSettingsExcist(shopName))
    {
        bool state;
        QString date = m_dataClass->GetModelSettingsByName(shopName,state).date;
        m_askDialog = new AskToUseSettingsDialog(shopName, date, this);
        connect(m_askDialog, &AskToUseSettingsDialog::ApplyPressed, this, &SqlDatabaseHandler::SendDataToSqlServer);
        connect(m_askDialog, &AskToUseSettingsDialog::EditPressed, this, &SqlDatabaseHandler::EmitSenderDialog);
        m_askDialog->show();
    }
    else
    {
        EmitSenderDialog(shopName);
    }


}



DataClass *SqlDatabaseHandler::GetDataClassEntity()
{
    return m_dataClass;
}



void SqlDatabaseHandler::SendDataToSqlServer(const QString &shopName)
{



    if(m_askDialog != nullptr)
    {
        m_askDialog->close();
    }

    bool state;

    ModelSettings settings = m_dataClass->GetModelSettingsByName(shopName, state);
    if(!state)
    {
        return;
    }
    ModelStruct modelStruct = m_dataClass->GetModelStructByName(shopName, state);
    if(!state)
    {
        return;
    }


    ClearSqlTable();

    QList<QString> keyList = settings.elementTypeMap.values();

    QVector<QVariantList> itemList = PrepareListData(modelStruct, settings);



    QSqlQuery query;
        query.prepare("INSERT INTO PRICE_LIST_TMP ( ClientID, ClientProductID, ClientVendorCode, ClientBrandName, ClientProductName, ClientPriceString, ClientPriceRecString, ClientStorageMark, CurrencyNameString)"
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);");

    for (auto item  : itemList)
    {
        for (auto property : item)
        {
            query.addBindValue(property);
        }
        if(!query.exec())
        {
            qDebug() <<"Error "<< query.lastError();
        }
    }


    bool success = EmitSqlScript();

    if(success)
    {
        settings.isSuccess = success;
        m_dataClass->InsertModelSettings(settings);
    }
}

void SqlDatabaseHandler::EmitSenderDialog(const QString &shop)
{
    if(m_askDialog != nullptr)
    {
        m_askDialog->close();
    }
    m_senderDataDialog = new SenderDataDialog(m_dataClass, shop, this);
    m_senderDataDialog->show();

    connect(m_senderDataDialog, &SenderDataDialog::SetingsHasCreated, this, &SqlDatabaseHandler::SendDataToSqlServer);

}

void SqlDatabaseHandler::SendAllDataToSqlServer()
{
    QStringList shopList = m_dataClass->GetSettingMap().keys();

    for(auto shopName : shopList )
    {
        bool state;

        ModelSettings settings = m_dataClass->GetModelSettingsByName(shopName, state);
        if(!state)
        {
            continue;
        }
        if(!settings.isSuccess)
        {
            continue;
        }

        ModelStruct modelStruct = m_dataClass->GetModelStructByName(shopName, state);
        if(!state)
        {
            continue;
        }


        ClearSqlTable();

        QList<QString> keyList = settings.elementTypeMap.values();

        QVector<QVariantList> itemList = PrepareListData(modelStruct, settings);


        QSqlQuery query;
        query.prepare("INSERT INTO PRICE_LIST_TMP ( ClientID, ClientProductID, ClientVendorCode, ClientBrandName, ClientProductName, ClientPriceString, ClientPriceRecString, ClientStorageMark, CurrencyNameString)"
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);");

        for (auto item  : itemList)
        {
            for (auto property : item)
            {
                query.addBindValue(property);
            }
            if(!query.exec())
            {
                qDebug() <<"Error "<< query.lastError();
            }
        }
            EmitSqlScript(settings.shop, false);
    }
    emit ShowMainWindow();
    QMessageBox::information(this, tr("Sql connection to server"),
                                     "Data has been sended ");
}



int SqlDatabaseHandler::CheckSqlTableRows()
{
    //TODO переделать
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PRICE_LIST_TMP");
    qDebug() << "Start row count";
    bool state = query.exec();
    if(state)
    {
        qDebug() << " HasFinished Success";
    }
    else
    {
        qDebug() << " HasFinished with Error"<< query.lastError();
    }

    qDebug() << "Number of Rows: " << query.value(0).toInt();
    return query.value(0).toInt();
}

bool SqlDatabaseHandler::EmitSqlScript(QString shopName, bool switchKey)
{
    //USE [unicomps]  EXEC [dbo].[ClientPriceLists_import_test]
    QSqlQuery query;
    query.prepare("USE [unicomps]  EXEC [dbo].[ClientPriceLists_import_test]");

    qDebug() << "Start sql script";
    bool state = query.exec();


    if(state)
    {
        if(!switchKey)
        {
            return state;
        }
        qDebug() << " HasFinished Success";
        QMessageBox::information(this, tr("Sql connection to server"),
                                         "Data has been sended "+shopName);
    }
    else
    {
        qDebug() << " HasFinished with Error"<< query.lastError().text();
        QMessageBox::warning(this, tr("Sql connection to server"),
                                         query.lastError().text());
    }

//    qDebug() << " HasFinished with"<< query.lastError().text();
//    QMessageBox::information(this, tr("Sql connection to server"),
//                                     query.lastError().text());

    return state;

}

bool SqlDatabaseHandler::EmitSqlRecount()
{
    // dbo.ClientPriceLists_recount_full
    QSqlQuery query;
    query.prepare("USE [unicomps]  EXEC [dbo].[ClientPriceLists_recount_full]");

    qDebug() << "Start sql script";
    bool state = query.exec();


    if(state)
    {

        qDebug() << " HasFinished Success";
        QMessageBox::information(this, tr("Sql connection to server"),
                                         "ClientPriceLists_recount_full finished success!");
    }
    else
    {
        qDebug() << " HasFinished with Error"<< query.lastError().text();
        QMessageBox::warning(this, tr("Sql connection to server"),
                                         query.lastError().text());
    }
    emit ShowMainWindow();
    return state;
}

bool SqlDatabaseHandler::ClearSqlTable()
{
    QSqlQuery query;
    query.prepare("USE [unicomps]  DELETE FROM [dbo].[PRICE_LIST_TMP]");
    qDebug() << "Start clear";
    bool state = query.exec();
    if(state)
    {
        qDebug() << " HasFinished Success";
    }
    else
    {
        qDebug() << " HasFinished with Error"<< query.lastError();
    }

    return state;

}

QVector<QVariantList> SqlDatabaseHandler::PrepareListData(ModelStruct& modelStruct, ModelSettings& settings)
{
    QVector<QVariantList> itemList;

    for(auto products : modelStruct.modelMap)
    {
        QVariantList productList;

        productList.append(settings.clientPriceListID);
        productList.append(0);

        for(int i = 0; i < ElementsType::LAST_TYPE; i++)
        {
            ElementsType tmpType = static_cast<ElementsType>(i);
            if(products.contains(settings.elementTypeMap.value(tmpType)))
            {
                productList.append( products.value(settings.elementTypeMap.value(tmpType)) );
            }
            else
            {
                productList.append("");
            }

        }
        productList.insert(productList.size()-2, 0);

        itemList.append(productList);
    }

    return itemList;

}
