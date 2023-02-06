#ifndef PARSINGDIALOG_HPP
#define PARSINGDIALOG_HPP

#include <QDialog>
#include "../Common/ModelStruct.hpp"
#include "SelectedParserElementWidget.hpp"

namespace Ui {
class ParsingDialog;
}

class ParsingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParsingDialog(const ModelStruct& modelStruct,QWidget *parent = nullptr);
    ~ParsingDialog();

private:

    void CreateSettingsWidget();
    Ui::ParsingDialog *ui;

    QVector<SelectedParserElementWidget*> m_widgetsSettingVec;
    ModelSettings m_settings;
    ModelStruct   m_modelStruct;

};

#endif // PARSINGDIALOG_HPP
