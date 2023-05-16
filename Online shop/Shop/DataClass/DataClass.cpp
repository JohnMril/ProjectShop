#include "DataClass.hpp"

DataClass::DataClass(QObject *parent) : QObject(parent)
{

}



void DataClass::InsertModelSettings(const ModelSettings &settings)
{
    m_settingsVec.append(settings);
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



ModelStruct DataClass::GetModelStructByName(const QString &shopName) const
{
    for(auto model : m_modelStructVec)
    {
        if (model.shop == shopName)
        {
            return model;
        }
    }

    return ModelStruct();
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
