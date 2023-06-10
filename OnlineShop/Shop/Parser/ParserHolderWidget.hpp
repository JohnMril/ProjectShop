#ifndef PARSERHOLDERWIDGET_HPP
#define PARSERHOLDERWIDGET_HPP

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "Parser.hpp"
#include "ParsingDialog.hpp"
#include "DataClass/DataClass.hpp"
#include "ChoseSettingsDialog.hpp"
#include "RawDataParser/LanitParser.hpp"
#include "RawDataParser/AsbisParser.hpp"
#include "RawDataParser/ParserRawDataInteface.hpp"

class ParserHolderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParserHolderWidget(QWidget *parent = nullptr);



    void SetDataClass(DataClass *dataClass);

    void DataLoaded(const int &apiEnum);


signals:

    void NewModelStructHasCreated();
    void NewModelLoaded(const QString&);

private slots:


private:


    QString EmitFileFinder();

    bool ParseByFilePath(QString path);

    void CallErorrMessageBox(QString text, QString title);

    Parser m_parser;

    QMap<API, ParserRawDataInteface*> m_parserMap;

    ParsingDialog* m_parserDialog;

    ChoseSettingsDialog* m_chooseSettingsDialog;

    DataClass* m_dataClass;

    QString m_lastFilePath = "C://";





};

#endif // PARSERHOLDERWIDGET_HPP