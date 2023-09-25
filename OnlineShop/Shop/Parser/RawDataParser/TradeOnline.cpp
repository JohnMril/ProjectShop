#include "TradeOnline.hpp"

TradeOnlineParser::TradeOnlineParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}

bool TradeOnlineParser::VParsing()
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



    QJsonArray settingArray = jDoc.object().value("Tovar").toArray();

    QVariantMap tmpMap;
    for(auto setting : settingArray)
    {
      tmpMap.clear();
      tmpMap = setting.toObject().toVariantMap();
      for(auto key : setting.toObject().keys())
      {
          m_modelStruct.setAttributs.insert(key);
      }
      m_modelStruct.setAttributs.insert("currency");
      tmpMap.insert("currency", "RUR");
      m_modelStruct.modelMap.push_back(tmpMap);
    }



    return true;
}
