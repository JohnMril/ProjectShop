#include "NetLabParser.hpp"


NetLabParser::NetLabParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}

bool NetLabParser::VParsing()
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

    QString fileArrayStr = QString::fromUtf8(fileArray);
    fileArrayStr.replace("}, {", "}]%%%%[{");

    QStringList splitedMessage = fileArrayStr.split("%%%%");
    qDebug() <<"products founded "<<splitedMessage.size();
    QJsonParseError* error = new QJsonParseError;
    for(auto splitPart : splitedMessage)
    {
        QJsonDocument jDoc = QJsonDocument::fromJson(splitPart.toUtf8(),error);
//        qDebug() << error->errorString();

        if(!jDoc.isArray())
        {
            qDebug() << "not array";
            return false;
        }
        QJsonArray mainArray = jDoc.array();


        for (auto product : mainArray)
        {
                int counter = 0;
            QVariantMap tmpMap = product.toObject().toVariantMap();
            for (auto key : product.toObject().keys())
            {
                if(key.contains("количество на"))
                {
                   counter += product.toObject().value(key).toInt();
                }
                m_modelStruct.setAttributs.insert(key);
            }
            tmpMap.insert("Общее количество на складах", counter);
            tmpMap.insert("ВалютаUSD", "USD");
            tmpMap.insert("ВалютаEUR", "EUR");
            m_modelStruct.setAttributs.insert("ВалютаUSD");
            m_modelStruct.setAttributs.insert("ВалютаEUR");
            m_modelStruct.setAttributs.insert("Общее количество на складах");
            m_modelStruct.modelMap.append(tmpMap);
        }
    }
    return true;
}
