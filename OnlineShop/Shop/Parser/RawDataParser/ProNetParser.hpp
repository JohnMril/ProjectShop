#ifndef PRONETPARSER_HPP
#define PRONETPARSER_HPP

#include "ParserRawDataInteface.hpp"

class ProNetParser : public ParserRawDataInteface
{
public:
    ProNetParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // PRONETPARSER_HPP
