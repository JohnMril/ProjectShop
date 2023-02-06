#ifndef PARSERHOLDERWIDGET_HPP
#define PARSERHOLDERWIDGET_HPP

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "Parser.hpp"
#include "ParsingDialog.hpp"

class ParserHolderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParserHolderWidget(QWidget *parent = nullptr);


    void AddNewFile();



signals:

    void NewModelStructHasCreated();

private:

    QString EmitFileFinder();

    bool ParseByFilePath(QString path);

    void CallErorrMessageBox(QString text, QString title);

    Parser m_parser;

    ParsingDialog* m_parserDialog;



};

#endif // PARSERHOLDERWIDGET_HPP
