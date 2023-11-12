#include "SqlDataClassThread.hpp"

SqlDataClassThread::SqlDataClassThread(DataClass *dataClass, QObject *parent)
    : QObject(parent), m_dataClass(dataClass)
{
    m_currentThread = new QThread();
    this->moveToThread(m_currentThread);

    connect(this, &SqlDataClassThread::SendAllSignal, this, &SqlDataClassThread::SendAllShops);
    connect(this, &SqlDataClassThread::SoloSendSignal, this, &SqlDataClassThread::SendSoloShop);
    connect(this, &SqlDataClassThread::RecountSignal, this, &SqlDataClassThread::RecountAll);
    connect(this, &SqlDataClassThread::MakeConnectionSignal, this, &SqlDataClassThread::MakeConnetion);

    m_currentThread->start();
}



bool SqlDataClassThread::MakeConnetion(QString serverAdres, QString dataBaseName, QString userName, QString password)
{
    m_dataBase = QSqlDatabase::addDatabase("QODBC");

    m_dataBase.setDatabaseName("DRIVER={SQL Server};SERVER="+serverAdres+";DATABASE="+dataBaseName+";");
    m_dataBase.setUserName(userName);
    m_dataBase.setPassword(password);

    if(m_dataBase.open())
    {
        qDebug() <<" SQL connection SUCCESS";
        m_isConnected = true;
        emit Connected(m_isConnected);
        return true;
    }
    qDebug() <<" SQL connection ERROR";
    m_isConnected = false;
    emit Connected(m_isConnected);
    return false;
}



bool SqlDataClassThread::SendDataToServer(QString name, const QVector<QVariantList> &productVec, QString &errorHandler)
{
    bool isPassed = true;
    emit Started(name);

    isPassed &= ClearSqlTable(errorHandler);

    if(!isPassed)
    {
        emit Finished(name);
        return isPassed;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO PRICE_LIST_TMP ( ClientID, ClientProductID, ClientVendorCode, ClientBrandName, ClientProductName, ClientPriceString, ClientPriceRecString, ClientStorageMark, CurrencyNameString)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);");

    for (auto item  : productVec)
    {
        for (auto property : item)
        {
            query.addBindValue(property);
        }
        if(!query.exec())
        {
            isPassed &= false;
            QString bindError = "SQL ERROR [ADDING VALU]"+ query.lastError().text() +"\n";
            qDebug() <<"Error "<< bindError;
            errorHandler += bindError;
        }
    }
    if(!isPassed)
    {
        emit Finished(name);
        return isPassed;
    }


    isPassed &= SqlScript(errorHandler);

    emit Finished(name);
    return isPassed;
}



bool SqlDataClassThread::ClearSqlTable(QString &error)
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
        error += query.lastError().text() + "\n";
    }


    return state;
}



bool SqlDataClassThread::SqlScript(QString &error)
{
    QSqlQuery query;
    query.prepare("USE [unicomps]  EXEC [dbo].[ClientPriceLists_import_test]");

    qDebug() << "Start sql script";
    bool state = query.exec();


    if(state)
    {

        qDebug() << " HasFinished Success";

    }
    else
    {
        qDebug() << " HasFinished with Error"<< query.lastError().text();
        error += query.lastError().text();
        ;
    }


    return state;
}



bool SqlDataClassThread::SqlRecount(QString &error)
{
    QSqlQuery query;
    query.prepare("USE [unicomps]  EXEC [dbo].[ClientPriceLists_recount_full]");

    qDebug() << "Start sql script";
    bool state = query.exec();


    if(state)
    {

        qDebug() << " HasFinished Success";

    }
    else
    {
        qDebug() << " HasFinished with Error"<< query.lastError().text();
        error+=query.lastError().text();
    }

    return state;
}



QString SqlDataClassThread::GetLastError()
{
    QString result = m_error;
    m_error = QString();
    return result;
}

void SqlDataClassThread::ThreadSoloSend(QString name)
{
    if(!m_isWork)
    {
        emit SoloSendSignal(name);
    }
    else
    {
        m_error = "Выполняется предыдущая команда!";
        emit EmitMessageBox(false);
    }
}

void SqlDataClassThread::ThreadAllSend()
{
    if(!m_isWork)
    {
        emit SendAllSignal();
    }
    else
    {
        m_error = "Выполняется предыдущая команда!";
        emit EmitMessageBox(false);
    }
}

void SqlDataClassThread::RecountSend()
{
    if(!m_isWork)
    {
        emit RecountSignal();
    }
    else
    {
        m_error = "Выполняется предыдущая команда!";
        emit EmitMessageBox(false);
    }
}

void SqlDataClassThread::ThreadMakeConnection(QString serverAdres, QString dataBaseName, QString userName, QString password)
{
    emit MakeConnectionSignal(serverAdres, dataBaseName, userName, password);
}



void SqlDataClassThread::SendSoloShop(QString name)
{
    bool state;

    m_isWork = true;
    emit Started(name);

    ModelSettings settings = m_dataClass->GetModelSettingsByName(name, state);
    if(!state)
    {
        return;
    }
    ModelStruct modelStruct = m_dataClass->GetModelStructByName(name, state);
    if(!state)
    {
        return;
    }

    QVector<QVariantList> itemList = PrepareListData(modelStruct, settings);

    QString error;

    state = SendDataToServer(name, itemList, error);
    m_error = error;
    emit EmitMessageBox(state);
    m_isWork = false;
    emit Finished(name);

}



void SqlDataClassThread::SendAllShops()
{
    m_isWork = true;
    QStringList shopList = m_dataClass->GetSettingMap().keys();
    QString error;
    bool stateAll = true;
    for (auto shopName : shopList)
    {
        emit Started("Происходит отправка на сервер поставщика "+shopName);
        bool state = true;
        ModelSettings settings = m_dataClass->GetModelSettingsByName(shopName, state);
        if(!state)
        {
            continue;
        }
        if(!settings.isSuccess)
        {
            emit Started("Поставщик: "+shopName +" ранее не был удачно отправлен.");
            m_currentThread->sleep(3);
            continue;
        }
        ModelStruct modelStruct = m_dataClass->GetModelStructByName(shopName, state);
        if(!state)
        {
            continue;
        }

        QVector<QVariantList> itemList = PrepareListData(modelStruct, settings);

        stateAll &= SendDataToServer(shopName, itemList, error);
    }

    emit Finished("Отправлены все доступные поставщики");

    m_error = error;
    EmitMessageBox(stateAll);
    m_isWork = false;
}



void SqlDataClassThread::RecountAll()
{
    bool state;
    QString error;
    m_isWork = true;
    emit Started("Выполняется скрипт Recount");
   state = SqlRecount(error);
   emit Finished("Скрипт Recount");
   emit EmitMessageBox(state);

   m_isWork = false;
}



QVector<QVariantList> SqlDataClassThread::PrepareListData(ModelStruct &modelStruct, ModelSettings &settings)
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
