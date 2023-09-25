#include "RRCParser.hpp"

RRCParser::RRCParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}

bool RRCParser::VParsing()
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

    while(!reader.atEnd())
    {
        reader.readNext();
        if (reader.isStartElement())
        {

            if (reader.name() == "item")
            {
               if(!tmpMap.isEmpty())
               {
                   tmpMap.insert("currency", "rub");
                   m_modelStruct.setAttributs.insert("currency");
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
