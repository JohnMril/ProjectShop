#ifndef PARSER_HPP
#define PARSER_HPP

#include "../Common/ModelStruct.hpp"

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
    
    bool ParsingFileToModel(QString pathToFile);
    
    ModelStruct GetModelStruct() const;

private:
    void ReadingFile(const QJsonValue& value, QVariant keyOfValue);

    void SplitingText(QString& text);
    
    ModelStruct m_lastModelStruct;

    QVector<QVariantMap> m_tmpModelVectorOfMap;

    ModelStruct m_tmpModelStuct;


};

#endif // PARSER_HPP
