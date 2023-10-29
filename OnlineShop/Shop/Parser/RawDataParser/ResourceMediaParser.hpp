#ifndef RESOURCEMEDIAPARSER_HPP
#define RESOURCEMEDIAPARSER_HPP


#include "ParserRawDataInteface.hpp"
class ResourceMediaParser : public ParserRawDataInteface
{
public:
    ResourceMediaParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // RESOURCEMEDIAPARSER_HPP
