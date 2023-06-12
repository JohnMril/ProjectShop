#ifndef MARVELPARSER_HPP
#define MARVELPARSER_HPP

#include <QMessageBox>

#include "ParserRawDataInteface.hpp"


class MarvelParser : public ParserRawDataInteface
{
public:
    MarvelParser(QString vendorName, QString fileName, QObject *parent = nullptr);

    bool VParsing() override;
};

#endif // MARVELPARSER_HPP
