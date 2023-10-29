#ifndef ELKOPARSER_HPP
#define ELKOPARSER_HPP


#include "ParserRawDataInteface.hpp"

class ElkoParser : public ParserRawDataInteface
{
public:
    ElkoParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // ELKOPARSER_HPP
