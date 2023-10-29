#include "OcsParser.hpp"


OcsParser::OcsParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}

bool OcsParser::VParsing()
{
    QMap<QString, ModelSettings> result;

    qDebug() <<m_pathToFile;
    QFile file(m_pathToFile);
    QFileInfo fileInfo(file);
    QDateTime dateTime = fileInfo.lastModified();
    m_modelStruct.date = dateTime.toString();

    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"ReadFileError path:"<< m_pathToFile;
        return false;
    }

    QByteArray fileArray = file.readAll();

    QJsonDocument jDoc = QJsonDocument::fromJson(fileArray);

    if(!jDoc.isObject())
    {
        return false;
    }



    QJsonArray settingArray = jDoc.object().value("result").toArray();

    QVariantMap tmpMap;
    int quantityCounter;
    for(auto setting : settingArray)
    {
      tmpMap.clear();
      quantityCounter = 0;

      QJsonObject mainObj =setting.toObject();

      QJsonObject productObj = mainObj.value("product").toObject();

      for (auto productElement : productObj.toVariantMap().toStdMap())
      {
          if(productElement.first == "catalogPath")
          {
              continue;
          }
          tmpMap.insert(productElement.first, productElement.second);
          m_modelStruct.setAttributs.insert(productElement.first);
      }

      QJsonObject priceObj = mainObj.value("price").toObject();

      for (auto priceElementKey : priceObj.keys())
      {
          if(priceObj.value(priceElementKey).isObject())
          {
              for(auto listElement : priceObj.value(priceElementKey).toObject().toVariantMap().toStdMap())
              {
                  tmpMap.insert(priceElementKey+listElement.first, listElement.second);
                  m_modelStruct.setAttributs.insert(priceElementKey+listElement.first);
              }
          }
          else
          {
              tmpMap.insert(priceElementKey, priceObj.value(priceElementKey));
              m_modelStruct.setAttributs.insert(priceElementKey);
          }
      }


      QJsonArray locationsArray = mainObj.value("locations").toArray();
      for(int i = 0; i < locationsArray.size(); i++)
      {
         QJsonObject locationObj = locationsArray.at(i).toObject();

         if(locationObj.value("location").toString().contains("МСК") || locationObj.value("location").toString().contains("СПБ"))
         {
            quantityCounter += locationObj.value("quantity").toObject().value("value").toInt();
         }
         for (auto locationElementKey : locationObj.keys())
         {
             if(locationObj.value(locationElementKey).isObject())
             {

                 for(auto listElement : locationObj.value(locationElementKey).toObject().toVariantMap().toStdMap())
                 {
                     tmpMap.insert(locationElementKey+listElement.first+QString::number(i), listElement.second);
                     m_modelStruct.setAttributs.insert(locationElementKey+listElement.first+QString::number(i));
                 }
             }
             else
             {
                 tmpMap.insert(locationElementKey+QString::number(i), locationObj.value(locationElementKey));
                 m_modelStruct.setAttributs.insert(locationElementKey+QString::number(i));
             }
         }
      }

      tmpMap.insert("Общее количество на складах", quantityCounter);
      m_modelStruct.setAttributs.insert("Общее количество на складах");
      m_modelStruct.modelMap.push_back(tmpMap);
    }



    return true;
}
