#ifndef INLINEPARSER_HPP
#define INLINEPARSER_HPP

#include "ParserRawDataInteface.hpp"

class InlineParser : public ParserRawDataInteface
{
public:
    InlineParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;

};

#endif // INLINEPARSER_HPP
