#include "MarvelParser.hpp"

MarvelParser::MarvelParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}



bool MarvelParser::VParsing()
{
    qDebug() <<m_pathToFile;
    QFile file(m_pathToFile);
    QFileInfo fileInfo(file);
    QDateTime dateTime = fileInfo.lastModified();
    m_modelStruct.date = dateTime.toString();

    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QXmlStreamReader reader(file.readAll());

    QVariantMap tmpMap;

    bool start = false;
    bool hasError = false;

    while(!reader.atEnd())
    {
        reader.readNext();
        if (reader.isStartElement())
        {
            if(reader.name() == "Code")
            {
                if(reader.readElementText().toInt() != 0)
                {
                    hasError = true;
                }
            }
            if((reader.name() == "Message")&&(hasError))
            {
                m_errorMessage = reader.readElementText();
                return false;
            }

            if (reader.name() == "CategoryItem")
            {
               if(!tmpMap.isEmpty())
               {
                   m_modelStruct.modelMap.push_back(tmpMap);
               }
               tmpMap = QVariantMap();
               start = true;
            }
            else if (start)
            {
                tmpMap.insert(reader.name().toString(), reader.readElementText(QXmlStreamReader::IncludeChildElements));
                m_modelStruct.setAttributs.insert(reader.name().toString());
            }
        }
    }
    if(!tmpMap.isEmpty())
    {
        m_modelStruct.modelMap.push_back(tmpMap);
    }

    qDebug()<< "Reading file " << m_fileName<<" has beenFinished";
    return true;
}
