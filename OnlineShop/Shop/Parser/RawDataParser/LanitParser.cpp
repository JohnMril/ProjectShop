#include "LanitParser.hpp"


LanitParser::LanitParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}



bool LanitParser::VParsing()
{
    qDebug() <<m_pathToFile;
    QFile file(m_pathToFile);
    QFileInfo fileInfo(file);
    QDateTime dateTime = fileInfo.lastModified();
    m_modelStruct.date = dateTime.toString();

    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader reader(file.readAll());
        file.close();
        while(!reader.atEnd())
        {
            reader.readNext();
            if (reader.isStartElement())
            {
                if (reader.name() == "position")
                {
                    QVariantMap tmpMap;
                    foreach(const QXmlStreamAttribute &attr, reader.attributes())
                    {
                        tmpMap.insert(attr.name().toString(), attr.value().toString());
                        m_modelStruct.setAttributs.insert(attr.name().toString());
                    }
                    m_modelStruct.modelMap.push_back(tmpMap);
                }
            }
        }
        qDebug()<< "Reading file " << m_fileName << " has beenFinished";
        return true;
    }
    else
    {
        return false;
    }
}
