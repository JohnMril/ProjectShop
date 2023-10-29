#include "InlineParser.hpp"

InlineParser::InlineParser(QString vendorName, QString fileName, QObject *parent)
    :ParserRawDataInteface(vendorName, fileName, parent)
{

}

bool InlineParser::VParsing()
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
                if (reader.name() == "g")
                {
                    QVariantMap tmpMap;
                    foreach(const QXmlStreamAttribute &attr, reader.attributes())
                    {
                        if(attr.name().toString() == "c")
                        {
                            if(attr.value().toString().contains("-"))
                            {
                                tmpMap.insert(attr.name().toString(), 0);
                            }
                            else
                            {
                                tmpMap.insert(attr.name().toString(), attr.value().toString());
                            }
                        }
                        else
                        {
                            tmpMap.insert(attr.name().toString(), attr.value().toString());
                        }
                        m_modelStruct.setAttributs.insert(attr.name().toString());
                    }
                    while (reader.name() != "n")
                    {
                        reader.readNext();
                    }
                    tmpMap.insert("name",  reader.readElementText());
                    while (reader.name() != "c")
                    {
                        reader.readNext();
                    }
                    //<b>Ноутбуки</b> » <b>Ноутбуки Lenovo</b> » <b>LENOVO</b>
                    QString comment = reader.readElementText();
                    tmpMap.insert("comment",  comment);

                    QString brand = comment.split("»", Qt::SplitBehaviorFlags::SkipEmptyParts).last();
                    brand.remove(" <b>");
                    brand.remove("</b>");
                    tmpMap.insert("brand",  brand);

                    m_modelStruct.setAttributs.insert("comment");
                    m_modelStruct.setAttributs.insert("brand");
                    m_modelStruct.setAttributs.insert("name");

                    tmpMap.insert("currency", "rub");
                    m_modelStruct.setAttributs.insert("currency");

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
