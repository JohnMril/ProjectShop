#ifndef TRADEONLINE_HPP
#define TRADEONLINE_HPP

#include "ParserRawDataInteface.hpp"

class TradeOnlineParser : public ParserRawDataInteface
{
public:
    TradeOnlineParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // TRADEONLINE_HPP
