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

        m_widgetsSettingVec.append(new SelectedParserElementWidget(key, number, ElementsType::TEXT, this));
        ui->gridLayout->addWidget(m_widgetsSettingVec.last());
        number++;
    }


}
