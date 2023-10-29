#include "ResourceMediaParser.hpp"



ResourceMediaParser::ResourceMediaParser(QString vendorName, QString fileName, QObject *parent)
:ParserRawDataInteface(vendorName, fileName, parent)
{

}

bool ResourceMediaParser::VParsing()
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

    QJsonArray mainArray = jDoc.array();

    for (auto product : mainArray)
    {
        QVariantMap tmpMap;

        QJsonObject objProduct = product.toObject();
        for(auto key : objProduct.keys())
        {
           tmpMap.insert(key, objProduct.value(key));
           m_modelStruct.setAttributs.insert(key);

        }

        tmpMap.insert("Валюта RUR", "RUR");
        m_modelStruct.setAttributs.insert("Валюта RUR");

        m_modelStruct.modelMap.push_back(tmpMap);


    }
    return true;
}
