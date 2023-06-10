#ifndef ASBISPARSER_HPP
#define ASBISPARSER_HPP

#include "ParserRawDataInteface.hpp"

class AsbisParser : public ParserRawDataInteface
{
public:
    AsbisParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // ASBISPARSER_HPP
