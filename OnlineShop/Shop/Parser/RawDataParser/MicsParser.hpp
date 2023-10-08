#ifndef MICSPARSER_HPP
#define MICSPARSER_HPP

#include "ParserRawDataInteface.hpp"

class MicsParser : public ParserRawDataInteface
{
public:
    MicsParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // MICSPARSER_HPP
