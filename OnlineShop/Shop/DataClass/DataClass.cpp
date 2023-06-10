#include "DataClass.hpp"

DataClass::DataClass(QObject *parent) : QObject(parent)
{

}



void DataClass::InsertModelSettings(const ModelSettings &settings)
{

    m_settingMap.insert(settings.shop, settings);
    emit NewSettingAdded();
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
    emit NewSettingAdded();
}



QMap<QString, ModelSettings> DataClass::GetSettingMap() const
{
    return m_settingMap;
}



void DataClass::SetSettingMap(const QMap<QString, ModelSettings> &settingMap)
{
    m_settingMap = settingMap;
}



QVariantMap DataClass::GetSqlConnectionSettings() const
{
    return m_sqlConnectionSettings;
}



void DataClass::SetSqlConnectionSettings(const QVariantMap &sqlConnectionSettings)
{
    m_sqlConnectionSettings = sqlConnectionSettings;
    emit NewSettingAdded();
}
