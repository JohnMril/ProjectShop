#include "AsbisParser.hpp"


AsbisParser::AsbisParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}



bool AsbisParser::VParsing()
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
            if (reader.name() == "PRICE")
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
                tmpMap.insert(reader.name().toString(), reader.readElementText());
                m_modelStruct.setAttributs.insert(reader.name().toString());
            }
        }
    }

    qDebug()<< "Reading file " << m_fileName<<" has beenFinished";
    return true;
}
