#ifndef NETLABPARSER_HPP
#define NETLABPARSER_HPP

#include "ParserRawDataInteface.hpp"

class NetLabParser : public ParserRawDataInteface
{
public:
    NetLabParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // NETLABPARSER_HPP
