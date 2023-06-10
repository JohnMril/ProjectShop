#include "ParsingDialog.hpp"
#include "ui_ParsingDialog.h"

ParsingDialog::ParsingDialog(const ModelStruct &modelStruct, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParsingDialog),
    m_modelStruct(modelStruct)
{
    ui->setupUi(this);

    CreateSettingsWidget();
}



ParsingDialog::ParsingDialog(const ModelSettings &modelSettings, const ModelStruct &modelStruct, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParsingDialog),
    m_settings(modelSettings),
    m_modelStruct(modelStruct)

{
    ui->setupUi(this);

    CreateUsedSettingsWidget();
}



ParsingDialog::~ParsingDialog()
{
    delete ui;
}



void ParsingDialog::CreateSettingsWidget()
{
    int number = 0;

    //TODO Кривая нумерация и кривое отображение типа данных
    for (auto key : m_modelStruct.modelMap.first().keys())
    {
        m_widgetsSettingVec.append(new SelectedParserElementWidget(key, number, this));
        ui->gridLayout->addWidget(m_widgetsSettingVec.last());
        number++;
    }
}



void ParsingDialog::CreateUsedSettingsWidget()
{
    int number = 0;

    //TODO Кривая нумерация и кривое отображение типа данных
    for (auto key : m_modelStruct.modelMap.first().keys())
    {
        ElementSettings tmpElement = m_settings.mapSettings.value(key);
        m_widgetsSettingVec.append(new SelectedParserElementWidget(key, number, this, tmpElement.type,
                                                                   tmpElement.enabled, tmpElement.valueName));
        ui->gridLayout->addWidget(m_widgetsSettingVec.last());
        number++;
    }
}



ModelStruct ParsingDialog::GetModelStruct() const
{
    return m_modelStruct;
}



ModelSettings ParsingDialog::GetSettings() const
{
    return m_settings;
}



void ParsingDialog::on_cancelButton_clicked()
{
    //TODO сделать messagebox

    this->close();
}



void ParsingDialog::on_okButton_clicked()
{
    bool state = true;

    QMap<ElementsType, int> counterMap;
    for (int i = 0; i < static_cast<int>(ElementsType::NOTHING); ++i)
    {
        counterMap.insert(static_cast<ElementsType>(i), 0);
    }


    for( auto widget : m_widgetsSettingVec)
    {
        ElementSettings tmpSettings = widget->GetSource();

        if(counterMap.contains(tmpSettings.type))
        {
            int &i = counterMap[tmpSettings.type];
            i++;
        }

        m_settings.mapSettings.insert(tmpSettings.keyName, tmpSettings);
    }
    m_settings.shop = m_modelStruct.shop;

    for (auto element : counterMap)
    {
        if(element!=1)
        {
            state = false;
        }
    }

    if(state)
    {
        emit okIsClicked();
    }
    else
    {
        qDebug()<< "settingsError";
    }
}
