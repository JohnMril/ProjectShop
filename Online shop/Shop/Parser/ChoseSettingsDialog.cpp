#include "ChoseSettingsDialog.hpp"
#include "ui_ChoseSettingsDialog.h"

ChoseSettingsDialog::ChoseSettingsDialog(QVector<ModelSettings>& settings, QWidget *parent) :
    QDialog(parent),
    m_vecSettings(settings),
    ui(new Ui::ChoseSettingsDialog)
{
    ui->setupUi(this);

    for(auto elem : settings)
    {
       m_listOfSettings.append( elem.shop);
    }

    ui->SettingsComboBox->addItems(m_listOfSettings);

    this->show();
}



ChoseSettingsDialog::~ChoseSettingsDialog()
{
    delete ui;
}



void ChoseSettingsDialog::on_ApplyPushButton_clicked()
{
    emit ApplyClicked(ui->SettingsComboBox->currentIndex());
}



void ChoseSettingsDialog::on_EdditPushButton_clicked()
{
    emit EdditClicked(ui->SettingsComboBox->currentIndex());
}



QVector<ModelSettings> ChoseSettingsDialog::GetVecSettings() const
{
    return m_vecSettings;
}
