#ifndef LOGICPARSER_HPP
#define LOGICPARSER_HPP


#include "ParserRawDataInteface.hpp"

class LogicParser : public ParserRawDataInteface
{
public:
    LogicParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // LOGICPARSER_HPP
