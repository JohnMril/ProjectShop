#ifndef DATACLASS_HPP
#define DATACLASS_HPP

#include <QObject>
#include <QVector>
#include <QSet>

#include "../Common/ModelStruct.hpp"

class DataClass : public QObject
{
    Q_OBJECT
public:
    explicit DataClass(QObject *parent = nullptr);

    void InsertModelSettings(const ModelSettings& settings);

    QSet<int> FindForSettings(const ModelStruct& modelStruct);

    void AppendNewModelStruct(const ModelStruct& model);

    QVector<ModelStruct> GetModelStructVec() const;
    ModelStruct* GetLastModelStruct() ;
    ModelStruct GetModelStructByName(const QString& shopName) const;
    void AddModelPair(const ModelStruct &modelStruct, const ModelSettings &modelSettings);

    ModelSettings* GetSettingsForModelStruct(ModelStruct* modelStructPtr);

private:
    QVector<ModelSettings> m_settingsVec;
    QVector<ModelStruct> m_modelStructVec;
    QMap<ModelStruct*,ModelSettings*> m_modelMap;



};

#endif // DATACLASS_HPP
