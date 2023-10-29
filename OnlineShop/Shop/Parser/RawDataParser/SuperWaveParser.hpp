#ifndef SUPERWAVEPARSER_HPP
#define SUPERWAVEPARSER_HPP

#include "ParserRawDataInteface.hpp"

class SuperWaveParser : public ParserRawDataInteface
{
public:
    SuperWaveParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // SUPERWAVEPARSER_HPP
