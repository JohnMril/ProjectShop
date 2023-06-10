#include "SettingHandler.hpp"

SettingHandler::SettingHandler(DataClass *dataClass, QObject *parent) : QObject(parent), m_dataClass(dataClass)

{
    m_settingDir = QDir::current();
    m_settingDir.cdUp();
    m_settingDir.cd("rawData");
}



bool SettingHandler::SettingSave()
{
    QMap<QString, ModelSettings> settingMap = m_dataClass->GetSettingMap();

    QJsonArray settingArray;

    for(auto setting : settingMap)
    {
         QJsonObject tmpSettingObject;

         tmpSettingObject.insert("ShopName", setting.shop);
         tmpSettingObject.insert("Date", setting.date);
         tmpSettingObject.insert("clientPriceListID", setting.clientPriceListID);

         QJsonObject tmpElementsMap;
         for(auto element : setting.elementTypeMap.toStdMap())
         {
             tmpElementsMap.insert(QString::number(element.first), element.second);
         }
         tmpSettingObject.insert("settingMap", tmpElementsMap);

         settingArray.append(tmpSettingObject);
    }

    QJsonObject rootObj;
    rootObj.insert("SettingArray", settingArray);
    QJsonDocument jDoc(rootObj);

    QFile file(m_settingDir.absolutePath() + "/modelSettings.json");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug()<<"ReadFileError path:"<< m_settingDir.path();
        return false;
    }

    file.write(jDoc.toJson());
    file.close();

    return true;
}



bool SettingHandler::SettingDownload()
{
    QMap<QString, ModelSettings> result;


    QFile file(m_settingDir.absolutePath() + "/modelSettings.json");

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"ReadFileError path:"<< m_settingDir.path();
        return false;
    }

    QByteArray fileArray = file.readAll();

    QJsonDocument jDoc = QJsonDocument::fromJson(fileArray);

    if(!jDoc.isObject())
    {
        return false;
    }



    QJsonArray settingArray = jDoc.object().value("SettingArray").toArray();

    for(auto setting : settingArray)
    {
        ModelSettings tmpSetting;
        QJsonObject settingObj = setting.toObject();

        tmpSetting.shop =  settingObj.value("ShopName").toString();
        tmpSetting.date =  settingObj.value("Date").toString();
        tmpSetting.clientPriceListID =  settingObj.value("clientPriceListID").toInt();
        QJsonObject elementsMap = settingObj.value("settingMap").toObject();

        QMap<ElementsType, QString> tmpElementMap;
        for(auto key : elementsMap.keys())
        {
            tmpElementMap.insert(static_cast<ElementsType>( key.toInt()), elementsMap.value(key).toString());
        }

        tmpSetting.elementTypeMap = tmpElementMap;
        result.insert(tmpSetting.shop, tmpSetting);
    }

    m_dataClass->SetSettingMap(result);

    return true;
}
