#include "SelectedParserElementWidget.hpp"


SelectedParserElementWidget::SelectedParserElementWidget(QString key, int number, QWidget *parent ,
                                                         ElementsType type ,
                                                         bool state , QString valueStr )
    : QWidget(parent)
{
    m_source.keyName = key;
    m_source.number = number;
    m_source.type = type;
    m_source.enabled = state;
    m_source.valueName = valueStr;


    for (int i = 0; i <= static_cast<int>(ElementsType::UNKNOWN_TYPE); ++i)
    {
        m_typeList.append(ConvertEnumToString(static_cast<ElementsType>(i)));
    }

    CreateWidgetBySource();
}



void SelectedParserElementWidget::CreateWidgetBySource()
{


   m_gridLayout =  new QGridLayout(this);
   this->setLayout(m_gridLayout);

   if(m_source.number == 0)
   {
       m_gridLayout->addWidget(new QLabel("Имя в файле", this), 0, 0);
       m_gridLayout->addWidget(new QLabel("Активировать эллемент", this), 0, 1);
       m_gridLayout->addWidget(new QLabel("Выберете номер", this), 0, 2);
       m_gridLayout->addWidget(new QLabel("Выберете имя", this), 0, 3);
       m_gridLayout->addWidget(new QLabel("Выберете тип", this), 0, 4);
   }

   m_keyNameLabel = new QLabel(m_source.keyName, this);
   m_gridLayout->addWidget(m_keyNameLabel, 2, 0);

   m_keyNameLabel->setMinimumWidth(160);

   bool  state = m_source.enabled;

   m_checkBox = new QCheckBox(this);
   m_checkBox->setChecked(state);
   connect(m_checkBox, &QCheckBox::clicked, this, &SelectedParserElementWidget::SwitchCheckBox);
   m_gridLayout->addWidget(m_checkBox, 2, 1);

   m_spinBox = new QSpinBox(this);
   m_spinBox->setValue(m_source.number);
   m_gridLayout->addWidget(m_spinBox, 2, 2);
   m_spinBox->setEnabled(state);

   m_lineEdit = new QLineEdit(m_source.valueName, this);
   m_gridLayout->addWidget(m_lineEdit, 2, 3);
   m_lineEdit->setEnabled(state);

   m_typeBox = new QComboBox(this);
   m_typeBox->addItems(m_typeList);
   m_typeBox->setCurrentIndex(m_source.type);
   m_gridLayout->addWidget(m_typeBox, 2, 4);
   m_typeBox->setEnabled(state);
}



void SelectedParserElementWidget::SaveToSource()
{
    m_source.enabled = m_checkBox->isChecked();
    m_source.valueName = m_lineEdit->text();
    m_source.number = m_spinBox->value();
    m_source.type = static_cast<ElementsType>(m_typeBox->currentIndex());
}



void SelectedParserElementWidget::SwitchCheckBox()
{
    bool stateBool =  m_checkBox->isChecked();

    m_spinBox->setEnabled(stateBool);
    m_lineEdit->setEnabled(stateBool);
    m_typeBox->setEnabled(stateBool);
}



ElementSettings SelectedParserElementWidget::GetSource()
{
    SaveToSource();
    return m_source;
}


