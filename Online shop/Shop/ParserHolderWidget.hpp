#ifndef PARSERHOLDERWIDGET_HPP
#define PARSERHOLDERWIDGET_HPP

#include <QWidget>
#include "Parser.hpp"

class ParserHolderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParserHolderWidget(QWidget *parent = nullptr);

signals:

private:

    Parser m_parser;



};

#endif // PARSERHOLDERWIDGET_HPP
