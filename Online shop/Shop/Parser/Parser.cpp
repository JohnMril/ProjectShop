#include "Parser.hpp"
#include <QDebug>

Parser::Parser()
{


}

bool Parser::ParsingFileToModel(QString pathToFile)
{
    QFile file(pathToFile);
    
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File :"<< pathToFile<< " can't be read!!!"<<endl;
        return false;
    }
    QString jsonByteArray = file.readAll();

    SplitingText(jsonByteArray);
    if(!m_tmpModelVectorOfMap.isEmpty())
    {
        m_tmpModelStuct.modelMap = m_tmpModelVectorOfMap;
        m_tmpModelStuct.date = QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");

        m_tmpModelStuct.shop = pathToFile.split("/").last().split(".").takeFirst() +m_tmpModelStuct.date.split(":").last();
        m_tmpModelVectorOfMap.clear();

        m_lastModelStruct = m_tmpModelStuct;
    }
    
    file.close();

    return true;
}

ModelStruct Parser::GetModelStruct() const
{
    return m_lastModelStruct;
}

void Parser::ReadingFile(const QJsonValue& value, QVariant keyOfValue)
{
    if (value.isObject())
    {
        qDebug() << "It's object "<< keyOfValue;
        for (auto key : value.toObject().keys())
        {
            ReadingFile(value.toObject().value(key), key);
        }
    }
    else if (value.isArray())
    {
        qDebug() << "It's array "<< keyOfValue;
        for (auto value0 : value.toArray())
        {
            ReadingFile(value0, keyOfValue);
        }
        
    }
    else
    {
        qDebug() << "It's end key "<< keyOfValue;
        qDebug() << "It's end value "<< value.toString();
    }
}

void Parser::SplitingText( QString& text)
{
    text.replace("[", "");
    QStringList objectList = text.split("]");


    for( const QString objectElem: objectList)
    {
        QStringList productList = objectElem.split("},");

        for (const QString productElem : productList)
        {
            QVariantMap tmpMapOfProduct;

            QStringList parameterList = productElem.split("\r\n");

            for (const QString parameterElem : parameterList)
            {
                if (!parameterElem.contains("':"))
                {
                    continue;
                }
                QStringList dataParameter = parameterElem.split("':");

                QPair<QVariant, QVariant> tmpPair;
                QVariant value;


                if (dataParameter.last().contains("',") || dataParameter.last().contains("None"))
                {
                    value = dataParameter.last().toStdString().data();
                }
                else
                {
                    if(dataParameter.last().contains(","))
                    {
                         value = dataParameter.last().replace(",", "");
                    }
                    value = dataParameter.last().toFloat();
                }

                QString keyOfValue = dataParameter.takeFirst();

                if(keyOfValue.contains(" "))
                {
                    keyOfValue.replace(" ", "");
                }
                if(keyOfValue.contains("'"))
                {
                    keyOfValue.replace("'", "");
                }

                tmpMapOfProduct.insert(keyOfValue, value);
            }

            if(!tmpMapOfProduct.isEmpty())
            {
                m_tmpModelVectorOfMap.append(tmpMapOfProduct);
            }
        }
    }
}

