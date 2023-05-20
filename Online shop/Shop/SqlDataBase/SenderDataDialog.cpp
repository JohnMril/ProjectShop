#include "SenderDataDialog.hpp"
#include "ui_SenderDataDialog.h"

SenderDataDialog::SenderDataDialog(DataClass *dataClass, QString modelStructName, QWidget *parent) :
    QDialog(parent),
    m_dataClass(dataClass),
    m_modelStructName(modelStructName),

    ui(new Ui::SenderDataDialog)
{
    ui->setupUi(this);
    FillWidgetByElements();
}

SenderDataDialog::~SenderDataDialog()
{
    delete ui;
}


void SenderDataDialog::on_sendPushButton_clicked()
{
    QMap<ElementsType, QString> elementsTypeMap;
    bool state = true;

    QMap<ElementsType, int> counterMap;
    for (int i = 0; i < static_cast<int>(ElementsType::NOTHING); ++i)
    {
        counterMap.insert(static_cast<ElementsType>(i), 0);
        elementsTypeMap.insert(static_cast<ElementsType>(i), 0);
    }

    for(auto element : m_elementVec)
    {
        if(elementsTypeMap.contains(element->GetType()))
        {
            elementsTypeMap[element->GetType()]= element->GetKeyName();
            int& i = counterMap[element->GetType()];
            i++;
        }
    }

    for(auto counter : counterMap.toStdMap())
    {
        if(counter.second > 1)
        {
            qDebug()<< ConvertEnumToString(counter.first)<<" chosen more than once";
            state = false;
        }
        if(counter.second == 0)
        {
            qDebug()<< ConvertEnumToString(counter.first)<<"not chosen";
            state = false;
        }
    }

    if(state)
    {
        ModelSettings settings;
        settings.shop = m_modelStructName;
        settings.date = QDateTime::currentDateTime().toString();
        settings.elementTypeMap = elementsTypeMap;
        settings.clientPriceListID = ui->ClientPriceListLineEdit->text().toInt();

        m_dataClass->InsertModelSettings(settings);

        emit SetingsHasCreated(m_modelStructName);
        this->close();
    }

}

void SenderDataDialog::FillWidgetByElements()
{
    bool stateSettings;
    ModelSettings settings = m_dataClass->GetModelSettingsByName(m_modelStructName, stateSettings);
    if(stateSettings)
    {
        ui->ClientPriceListLineEdit->setText(QString::number(settings.clientPriceListID));
    }


    bool stateModel;
    ModelStruct model = m_dataClass->GetModelStructByName(m_modelStructName, stateModel);
    if(!stateModel)
    {
        qDebug()<< "Model cant be found"<<m_modelStructName;
        return;
    }



    for(auto keyName : model.setAttributs)
    {
        ElementsType keyType = ElementsType::NOTHING;
        if(stateSettings)
        {
            if(settings.elementTypeMap.values().contains(keyName))
            {
                keyType = settings.elementTypeMap.key(keyName);
            }
        }

        SqlElement* element = new SqlElement(keyName, keyType, this);

        ui->elementVerticalLayout->addWidget(element);
        m_elementVec.push_back(element);

    }


}
