#include "ParserRawDataInteface.hpp"

ParserRawDataInteface::ParserRawDataInteface(QString vendorName, QString fileName, QObject *parent)
    : QObject(parent),  m_vendorName(vendorName), m_fileName(fileName)
{
    QDir currentDir;
    currentDir.setPath(QDir::currentPath());
    currentDir.cdUp();
    currentDir.cd("rawData");
    m_pathToFile = currentDir.path()+"/"+fileName;

    //TODO убрать после отладки + может поменять на поиск?
    qDebug()<< m_pathToFile;
    m_modelStruct.shop = m_vendorName;
}

ModelStruct ParserRawDataInteface::GetModelStruct()
{
    return m_modelStruct;
}

QString ParserRawDataInteface::GetErrorMessage() const
{
    return m_errorMessage;
}
