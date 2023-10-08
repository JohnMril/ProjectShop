#include "MicsParser.hpp"

MicsParser::MicsParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}

bool MicsParser::VParsing()
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
        int allcouter = 0;
        double money = 0;
        QString curency = "";
        QJsonObject tmpProduct = product.toObject();
        for(auto key :  tmpProduct.keys())
        {
            if(key != "Склады")
            {
                tmpMap.insert(key, tmpProduct.value(key));
                m_modelStruct.setAttributs.insert(key);
            }
            else
            {
                auto vultObj = tmpProduct.value(key).toObject();
                for(auto vultKey : vultObj.keys())
                {
                    auto soloVult = vultObj.value(vultKey).toObject();
                    for(auto soloVultKey : soloVult.keys())
                    {
                        if(soloVultKey == "Остаток")
                        {
                            QString count = soloVult.value(soloVultKey).toString();
                            if(count.contains("+"))
                            {
                                count.remove("+");
                            }
                            allcouter += count.toInt();
                        }

                        if(soloVultKey == "Цена")
                        {
                            QString monetStr = soloVult.value(soloVultKey).toString();
                            if(monetStr.toDouble() > money)
                            {
                                money = monetStr.toDouble();
                                curency = soloVult.value("Валюта").toString();
                            }
                        }
                        tmpMap.insert(vultKey+soloVultKey, soloVult.value(soloVultKey));
                        m_modelStruct.setAttributs.insert(vultKey+soloVultKey);
                    }
                }
            }
        }
        tmpMap.insert("Валюта", curency);
        m_modelStruct.setAttributs.insert("Валюта");
        tmpMap.insert("Цена", money);
        m_modelStruct.setAttributs.insert("Цена");

        tmpMap.insert("Общее количество на складах", allcouter);
        m_modelStruct.setAttributs.insert("Общее количество на складах");
        m_modelStruct.modelMap.push_back(tmpMap);
    }
    return true;
}

