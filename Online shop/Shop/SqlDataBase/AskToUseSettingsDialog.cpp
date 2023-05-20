#include "AskToUseSettingsDialog.hpp"
#include "ui_AskToUseSettingsDialog.h"

AskToUseSettingsDialog::AskToUseSettingsDialog(QString shopName, QString date, QWidget *parent) :
    QDialog(parent),
    m_shopName(shopName),
    ui(new Ui::AskToUseSettingsDialog)
{  


    ui->setupUi(this);
    ui->shopNameLabel->setText("Do you want to use excited Settings for "+ shopName);
    ui->DateLabel->setText("created date:"+ date);
}



AskToUseSettingsDialog::~AskToUseSettingsDialog()
{
    delete ui;
}



void AskToUseSettingsDialog::on_ApplyPushButton_clicked()
{
    emit ApplyPressed(m_shopName);
}



void AskToUseSettingsDialog::on_EditPushButton_clicked()
{
    emit EditPressed(m_shopName);
}
