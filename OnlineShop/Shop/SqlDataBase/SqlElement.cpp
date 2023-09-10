#include "SqlElement.hpp"
#include "ui_SqlElement.h"

SqlElement::SqlElement(QString keyName, ElementsType type, QWidget *parent) :
    QWidget(parent),
    m_keyName(keyName),
    m_type(type),
    ui(new Ui::SqlElement)
{
    ui->setupUi(this);
    ui->keyLabel->setText(keyName);

    QStringList typeList;
    for (int i = 0; i <= ElementsType::LAST_TYPE; i++)
    {
        typeList.append(ConvertEnumToString(static_cast<ElementsType>(i)));
    }

    ui->enumComboBox->addItems(typeList);

    ui->enumComboBox->setCurrentIndex(type);
}



SqlElement::~SqlElement()
{
    delete ui;
}



void SqlElement::on_enumComboBox_currentIndexChanged(int index)
{
    m_type = static_cast<ElementsType>(index);
}



ElementsType SqlElement::GetType() const
{
    return m_type;
}



QString SqlElement::GetKeyName() const
{
    return m_keyName;
}
