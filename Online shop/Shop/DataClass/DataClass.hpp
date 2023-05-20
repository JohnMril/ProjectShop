#ifndef DATACLASS_HPP
#define DATACLASS_HPP

#include <QObject>
#include <QVector>
#include <QSet>
#include <QDebug>

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
    ModelStruct* GetLastModelStruct();
    ModelStruct GetModelStructByName(const QString& shopName, bool& state) const;
    ModelSettings GetModelSettingsByName(const QString& shopName, bool& state) const;

    void AddModelPair(const ModelStruct &modelStruct, const ModelSettings &modelSettings);

    ModelSettings* GetSettingsForModelStruct(ModelStruct* modelStructPtr);

    QVector<ModelSettings> GetSettingsVec() const;

    QVector<QVariantList> GetDataListToSql(QString shop, QString date, bool &state);

    QVector<QVariantList> GetDataListToSqlDb(QString shop, bool& state);

    bool IsSettingsExcist(QString shopName);
    bool IsModelExcist(QString shopName);

    void AddModelStruct(const ModelStruct& modelStruct);
    void AddModelSettings(const ModelSettings& modelSettings);

private:
    QVector<ModelSettings> m_settingsVec;
    QVector<ModelStruct> m_modelStructVec;
    QMap<ModelStruct*, ModelSettings*> m_modelMap;

    QMap<QString, ModelStruct> m_modelMapNew;
    QMap<QString, ModelSettings> m_settingMap;


    //TODO Сделать сохранение класса в файл



};

#endif // DATACLASS_HPP
