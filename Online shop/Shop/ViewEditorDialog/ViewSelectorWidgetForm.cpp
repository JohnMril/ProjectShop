#include "ViewSelectorWidgetForm.hpp"
#include "ui_ViewSelectorWidgetForm.h"

ViewSelectorWidgetForm::ViewSelectorWidgetForm(int number, QString keyName, bool state, QWidget *parent) :
    QWidget(parent),
    m_number(number),
    m_keyName(keyName),
    ui(new Ui::ViewSelectorWidgetForm)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(state);

    ui->numberLabel->setText(QString::number(number));
    ui->checkBox->setText(keyName);

    connect(ui->checkBox, &QCheckBox::clicked, this, &ViewSelectorWidgetForm::EmitSignal);

}



ViewSelectorWidgetForm::~ViewSelectorWidgetForm()
{
    delete ui;
}



bool ViewSelectorWidgetForm::isChecked()
{
    return ui->checkBox->isChecked();
}



void ViewSelectorWidgetForm::SetChecked(bool state)
{
    ui->checkBox->setChecked(state);
    EmitSignal();
}



void ViewSelectorWidgetForm::EmitSignal()
{
    emit checkBoxClicked(m_number);
}
