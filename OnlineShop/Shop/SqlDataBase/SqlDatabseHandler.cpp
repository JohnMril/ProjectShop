#include "SqlDatabseHandler.hpp"

SqlDatabaseHandler::SqlDatabaseHandler(DataClass *dataClass, QWidget *parent) :
    QWidget(parent),
    m_dataClass(dataClass)
{
    m_sqlThread = new SqlDataClassThread(dataClass);

    connect(m_sqlThread, &SqlDataClassThread::Started, this, &SqlDatabaseHandler::Started);
    connect(m_sqlThread, &SqlDataClassThread::Finished, this, &SqlDatabaseHandler::Finished);
    connect(m_sqlThread, &SqlDataClassThread::EmitMessageBox, this, &SqlDatabaseHandler::MessageBoxFromThread);
    connect(m_sqlThread, &SqlDataClassThread::Connected, this, &SqlDatabaseHandler::ConnectionCreated);

}

bool SqlDatabaseHandler::isConnected() const
{
    return m_isConnected;
}

bool SqlDatabaseHandler::MakeConection(QString serverAdres, QString dataBaseName, QString userName, QString password)
{
//    m_dataBase = QSqlDatabase::addDatabase("QODBC");

//    m_dataBase.setDatabaseName("DRIVER={SQL Server};SERVER="+serverAdres+";DATABASE="+dataBaseName+";");
//    m_dataBase.setUserName(userName);
//    m_dataBase.setPassword(password);

    m_sqlThread->ThreadMakeConnection (serverAdres, dataBaseName, userName, password);


        return true;

}

void SqlDatabaseHandler::MakeConnection()
{
    auto settingMap = m_dataClass->GetSqlConnectionSettings();

    m_sqlThread->ThreadMakeConnection(settingMap.value("serverAdres").toString(),settingMap.value("dataBaseName").toString(),
                                      settingMap.value("userName").toString(),settingMap.value("password").toString());
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
    m_sqlThread->ThreadSoloSend(shopName);
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
   m_sqlThread->ThreadAllSend();
}



//int SqlDatabaseHandler::CheckSqlTableRows()
//{
//    //TODO переделать
//    QSqlQuery query;
//    query.prepare("SELECT COUNT(*) FROM PRICE_LIST_TMP");
//    qDebug() << "Start row count";
//    bool state = query.exec();
//    if(state)
//    {
//        qDebug() << " HasFinished Success";
//    }
//    else
//    {
//        qDebug() << " HasFinished with Error"<< query.lastError();
//    }

//    qDebug() << "Number of Rows: " << query.value(0).toInt();
//    return query.value(0).toInt();
//}

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

      m_sqlThread->RecountSend();

      return true;
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



void SqlDatabaseHandler::MessageBoxFromThread(bool state)
{
    QString error;
    if(state)
    {

        qDebug() << " HasFinished Success";
        QMessageBox::information(this, tr("Sql connection to server"),
                                         "Data sended, finished success!");
    }
    else
    {
        error = m_sqlThread->GetLastError();
        qDebug() << " HasFinished with Error"<< error;
        QMessageBox::warning(this, tr("Sql connection to server"),
                                         error);
    }
    emit ShowMainWindow();
}

void SqlDatabaseHandler::ConnectionCreated(bool state)
{
    QString error = "Ошибка соединения!";
    if(state)
    {

//        qDebug() << "ed Connect to sql";
//        QMessageBox::information(this, tr("Sql connection to server"),
//                                         "Connection finished success!");
        m_isConnected = true;
    }
    else
    {
        qDebug() << " HasFinished with Error"<< error;
        QMessageBox::warning(this, tr("Sql connection to server"),
                                         error);
        m_isConnected = false;
    }
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
                productList.append( products.value(settings.elementTypeMap.value(tmpType)).toString() );
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
