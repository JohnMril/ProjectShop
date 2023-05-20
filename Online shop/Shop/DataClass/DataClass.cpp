#include "DataClass.hpp"

DataClass::DataClass(QObject *parent) : QObject(parent)
{

}



void DataClass::InsertModelSettings(const ModelSettings &settings)
{
    m_settingMap.insert(settings.shop, settings);
}



QSet<int> DataClass::FindForSettings(const ModelStruct &modelStruct)
{
    QSet<int> result;
    bool stateBool = true;
    int numberOfmodel = -1;
    for ( auto model : m_settingsVec)
    {
        stateBool = true;
        numberOfmodel++;
        for (auto key : model.mapSettings.keys())
        {
            if(!modelStruct.modelMap.first().keys().contains(key))
            {
                stateBool = false;
                break;
            }
        }
        if(stateBool)
        {
            result.insert(numberOfmodel);
        }
    }

    return result;
}



void DataClass::AppendNewModelStruct(const ModelStruct &model)
{
    m_modelStructVec.append(model);
}



QVector<ModelStruct> DataClass::GetModelStructVec() const
{
    return m_modelStructVec;
}



ModelStruct* DataClass::GetLastModelStruct()
{
    if(!m_modelStructVec.isEmpty())
    return &m_modelStructVec[m_modelStructVec.size()-1];

    return nullptr;
}



ModelStruct DataClass::GetModelStructByName(const QString &shopName, bool& state) const
{
    if(m_modelMapNew.contains(shopName))
    {
        state = true;
        return m_modelMapNew.value(shopName);
    }
    state = false;
    return ModelStruct();
}

ModelSettings DataClass::GetModelSettingsByName(const QString &shopName, bool &state) const
{
    if(m_settingMap.contains(shopName))
    {
        state = true;
        return m_settingMap.value(shopName);
    }
    state = false;
    return ModelSettings();

}



void DataClass::AddModelPair(const ModelStruct &modelStruct, const ModelSettings &modelSettings)
{
    if(!m_modelStructVec.contains(modelStruct))
    {
        m_modelStructVec.append(modelStruct);
    }

    if(!m_settingsVec.contains(modelSettings))
    {
        m_settingsVec.append(modelSettings);
    }
 //FIXME chert
    m_modelMap.insert(&m_modelStructVec[m_modelStructVec.indexOf(modelStruct)],
            &m_settingsVec[m_settingsVec.indexOf(modelSettings)]);
}



ModelSettings *DataClass::GetSettingsForModelStruct(ModelStruct *modelStructPtr)
{
    return m_modelMap.value(modelStructPtr);
}



QVector<ModelSettings> DataClass::GetSettingsVec() const
{
    return m_settingsVec;
}



QVector<QVariantList> DataClass::GetDataListToSql(QString shop, QString date, bool &state)
{
    QStringList keyList;
    QVector<QVariantList> result;
    for(auto &model : m_modelStructVec)
    {
        if((model.shop == shop)&&(model.date == date))
        {
            if(m_modelMap.contains(&model))
            {
                ModelSettings* tmpSettings = m_modelMap.value(&model);
                for(int type = 0 ; type < ElementsType::NOTHING; type++)
                {
                    for(auto elememtSettings : tmpSettings->mapSettings)
                    {
                        if(elememtSettings.type == type)
                        {
                            keyList.append(elememtSettings.keyName);
                        }
                    }
                }

                for(auto productMap : model.modelMap)
                {
                    QVariantList tmpVariantList;
                    for(auto key : keyList)
                    {
                        tmpVariantList.append(productMap.value(key));
                    }
                    result.append(tmpVariantList);
                }
            }
        }
    }

    if(result.isEmpty())
    {
        state = false;
    }
    return result;
}

QVector<QVariantList> DataClass::GetDataListToSqlDb(QString shop, bool &state)
{
    if(!m_modelMapNew.contains(shop))
    {
        state = false;
        qDebug()<< "ModelStruct not founded by name:"<< shop;
    }
    if(!m_settingMap.contains(shop))
    {
        state = false;

        qDebug()<< "ModelSettings not founded by name:"<< shop;
    }




}

bool DataClass::IsSettingsExcist(QString shopName)
{
    return m_settingMap.contains(shopName);
}

bool DataClass::IsModelExcist(QString shopName)
{
    return m_modelMapNew.contains(shopName);
}



void DataClass::AddModelStruct(const ModelStruct &modelStruct)
{
    m_modelMapNew.insert(modelStruct.shop, modelStruct);
}



void DataClass::AddModelSettings(const ModelSettings &modelSettings)
{
    m_settingMap.insert(modelSettings.shop, modelSettings);
}
