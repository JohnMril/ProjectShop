#ifndef RRCPARSER_HPP
#define RRCPARSER_HPP

#include "ParserRawDataInteface.hpp"

class RRCParser : public ParserRawDataInteface
{
public:
    RRCParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // RRCPARSER_HPP
