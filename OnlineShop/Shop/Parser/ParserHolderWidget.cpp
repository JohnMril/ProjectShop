#include "ParserHolderWidget.hpp"

ParserHolderWidget::ParserHolderWidget(QWidget *parent) : QWidget(parent)
{

}





QString ParserHolderWidget::EmitFileFinder()
{
    QString filter = "All File (*.*);; Text File (*.txt);; XML File (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", m_lastFilePath,filter);

    QStringList splitPath = file_name.split("/");
    splitPath.takeLast();
    m_lastFilePath.clear();
    for (auto elem : splitPath)
    {
        m_lastFilePath.append(elem);
        m_lastFilePath.append("/");
    }

    return file_name;
}



bool ParserHolderWidget::ParseByFilePath(QString path)
{
    //TODO Добавить парсинг в зависимости от типа файла.
    return m_parser.ParsingFileToModel(path);
}



void ParserHolderWidget::CallErorrMessageBox(QString text, QString title)
{
    //TODO переделать под messageBox

    qDebug() << text<< title;

    QMessageBox::warning(this, title,
                         text);
}



void ParserHolderWidget::SetDataClass(DataClass *dataClass)
{
    m_dataClass = dataClass;
}



void ParserHolderWidget::DataLoaded(const int &apiEnum)
{
    m_parserMap.insert(API::LANIT,new LanitParser("Lanit", "LanitProducts.txt", this));
    m_parserMap.insert(API::ASBIS, new AsbisParser("Asbis", "asbisProducts.txt", this));
    m_parserMap.insert(API::MARVEL, new MarvelParser("Marvel", "MarvelProducts.txt", this));
    m_parserMap.insert(API::RRC, new RRCParser("RRC", "RRCProducts.txt", this));
    m_parserMap.insert(API::INLINE, new InlineParser("Inline", "InlineProducts.txt", this));
    m_parserMap.insert(API::PRONET, new ProNetParser("ProNet", "PronetProducts.txt", this));
    m_parserMap.insert(API::TRADEONLINE, new TradeOnlineParser("TradeOnline", "TradeOnlineProducts.txt", this));
    m_parserMap.insert(API::OCS, new OcsParser("Ocs", "OcsProducts.txt", this));
    m_parserMap.insert(API::MICS, new MicsParser("Mics", "MicsProducts.txt", this));
    m_parserMap.insert(API::NETLAB, new NetLabParser("NetLab", "NetLabProducts.txt", this));
    m_parserMap.insert(API::ELKO, new ElkoParser("Elko", "ElkoProducts.txt", this));
    m_parserMap.insert(API::SUPERWAVE, new SuperWaveParser("SuperWave", "SuperWaveProducts.txt", this));
    m_parserMap.insert(API::RESOURCEMEDIA, new ResourceMediaParser("ResourceMedia", "ResourceMediaProducts.txt", this));

    m_parserMap.insert(API::Logic, new LogicParser("3Logic", "3LogicProducts.txt", this));




    API tmpApi = static_cast<API>(apiEnum);
    if(m_parserMap.contains(tmpApi))
    {
        if(m_parserMap.value(tmpApi)->VParsing())
        {

            ModelStruct m_lastModel = m_parserMap.value(tmpApi)->GetModelStruct();
            m_dataClass->AddModelStruct(m_lastModel);
            emit NewModelLoaded(m_lastModel.shop);

        }
        else
        {
            CallErorrMessageBox(m_parserMap.value(tmpApi)->GetErrorMessage());
        }

    }

    for(auto parser : m_parserMap)
    {
        parser->deleteLater();
    }
    m_parserMap.clear();
}
