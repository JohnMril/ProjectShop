#include "ElkoParser.hpp"


ElkoParser::ElkoParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}



bool ElkoParser::VParsing()
{
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

    if(!jDoc.isArray())
    {
        return false;
    }
    QJsonArray settingArray = jDoc.array();

    QVariantMap tmpMap;

    for(auto product : settingArray)
    {
        tmpMap.clear();
        QJsonObject productObj = product.toObject();
        for(auto key : productObj.keys())
        {
            if(key == "events")
            {
                continue;
            }
            else if(key.contains("inTransit") or key.contains("inStock"))
            {
                QJsonArray array = productObj.value(key).toArray();
                for(auto element : array)
                {
                    QJsonObject elementObj = element.toObject();

                    tmpMap.insert(key+elementObj.value("stock").toString(), elementObj.value("quantity"));
                    m_modelStruct.setAttributs.insert(key+elementObj.value("stock").toString());
                }
            }
            else
            {
                tmpMap.insert(key, productObj.value(key));
                m_modelStruct.setAttributs.insert(key);
            }
        }
        tmpMap.insert("ВалютаRUR", "RUR");
        m_modelStruct.setAttributs.insert("ВалютаRUR");
        tmpMap.insert("Пустой бренд", "");
        m_modelStruct.setAttributs.insert("Пустой бренд");

        m_modelStruct.modelMap.push_back(tmpMap);
    }

    return true;
}
