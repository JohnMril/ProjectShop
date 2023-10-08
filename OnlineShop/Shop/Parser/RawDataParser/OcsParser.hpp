#ifndef OCSPARSER_HPP
#define OCSPARSER_HPP


#include "ParserRawDataInteface.hpp"

class OcsParser : public ParserRawDataInteface
{
public:
    explicit OcsParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // OCSPARSER_HPP
