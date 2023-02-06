#include "DataClass.hpp"

DataClass::DataClass(QObject *parent) : QObject(parent)
{

}



void DataClass::Insert(const ModelSettings &settings)
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



ModelStruct DataClass::GetLastModelStruct() const
{
    return m_modelStructVec.last();
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
