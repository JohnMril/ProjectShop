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
    explicit ParsingDialog(const ModelStruct& GetModelStruct,QWidget *parent = nullptr);

    explicit ParsingDialog(const ModelSettings& modelSettings, const ModelStruct& modelStruct, QWidget* parent = nullptr);
    ~ParsingDialog();

    ModelSettings GetSettings() const;

    ModelStruct GetModelStruct() const;

signals:
    void okIsClicked();

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:

    void CreateSettingsWidget();

    void CreateUsedSettingsWidget();

    Ui::ParsingDialog *ui;

    QVector<SelectedParserElementWidget*> m_widgetsSettingVec;
    ModelSettings m_settings;
    ModelStruct   m_modelStruct;

};

#endif // PARSINGDIALOG_HPP
