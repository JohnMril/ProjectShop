#ifndef PARSERRAWDATAINTEFACE_HPP
#define PARSERRAWDATAINTEFACE_HPP

#include <QObject>
#include <QDir>
#include <QDebug>
#include <QXmlStreamReader>
#include <QSet>
#include <QDateTime>

#include "Common/ModelStruct.hpp"

class ParserRawDataInteface : public QObject
{
    Q_OBJECT
public:
    explicit ParserRawDataInteface(QString vendorName, QString fileName, QObject *parent = nullptr);

    ModelStruct GetModelStruct();


    virtual bool VParsing() = 0;



    QString GetErrorMessage() const;

signals:


protected:
    QString     m_vendorName;
    QString     m_pathToFile;
    QString     m_fileName;
    QString     m_errorMessage = "Error at reading!";
    ModelStruct m_modelStruct;



};

#endif // PARSERRAWDATAINTEFACE_HPP
