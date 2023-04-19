#include "ParserRawDataInteface.hpp"

ParserRawDataInteface::ParserRawDataInteface(QString vendorName, QString fileName, QObject *parent)
    : QObject(parent),  m_vendorName(vendorName), m_fileName(fileName)
{
    m_pathToFile = QDir::currentPath()+"/rawData/"+fileName;
    //TODO убрать после отладки + может поменять на поиск?
    qDebug()<< m_pathToFile;
    m_modelStruct.shop = m_vendorName;
}

ModelStruct ParserRawDataInteface::GetModelStruct()
{
    return m_modelStruct;
}
