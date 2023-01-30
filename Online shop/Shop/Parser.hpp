#ifndef PARSER_HPP
#define PARSER_HPP

#include "ModelStruct.hpp"

#include <QVector>
#include <QString>
#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QFile>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QDateTime>

class Parser 
{
public:
    Parser();
    
    void ParsingFileToModel(QString pathToFile);
    
    QVector<ModelStruct> GetVecModelStruct() const;
    ModelStruct GetLastModel();

private:
    void ReadingFile(const QJsonValue& value, QVariant keyOfValue);

    void SplitingText(QString& text);
    
    QVector<ModelStruct> m_vecModelStruct;

    QVector<QVariantMap> m_tmpModelVectorOfMap;

    ModelStruct m_tmpModelStuct;


};

#endif // PARSER_HPP
