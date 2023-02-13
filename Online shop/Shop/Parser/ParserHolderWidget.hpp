#ifndef PARSERHOLDERWIDGET_HPP
#define PARSERHOLDERWIDGET_HPP

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "Parser.hpp"
#include "ParsingDialog.hpp"
#include "DataClass/DataClass.hpp"
#include "ChoseSettingsDialog.hpp"

class ParserHolderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParserHolderWidget(QWidget *parent = nullptr);


    void AddNewFile();



    void SetDataClass(DataClass *dataClass);

signals:

    void NewModelStructHasCreated();

private slots:
    void DialogSuccess();

    void ChooseSettings();

private:

    void SettingApply(const int& index);
    void SettingEdit (const int& index);


    QString EmitFileFinder();

    bool ParseByFilePath(QString path);

    void CallErorrMessageBox(QString text, QString title);

    Parser m_parser;

    ParsingDialog* m_parserDialog;

    ChoseSettingsDialog* m_chooseSettingsDialog;

    DataClass* m_dataClass;

    QString m_lastFilePath = "C://";



};

#endif // PARSERHOLDERWIDGET_HPP
