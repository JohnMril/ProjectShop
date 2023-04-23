#ifndef LANITPARSER_HPP
#define LANITPARSER_HPP

#include "ParserRawDataInteface.hpp"

class LanitParser : public ParserRawDataInteface
{
public:
    LanitParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // LANITPARSER_HPP
