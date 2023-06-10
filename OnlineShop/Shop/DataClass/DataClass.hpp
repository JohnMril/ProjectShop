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



    ModelStruct* GetLastModelStruct();
    ModelStruct GetModelStructByName(const QString& shopName, bool& state) const;
    ModelSettings GetModelSettingsByName(const QString& shopName, bool& state) const;




    bool IsSettingsExcist(QString shopName);
    bool IsModelExcist(QString shopName);

    void AddModelStruct(const ModelStruct& modelStruct);
    void AddModelSettings(const ModelSettings& modelSettings);

    QMap<QString, ModelSettings> GetSettingMap() const;
    void SetSettingMap(const QMap<QString, ModelSettings> &GetSettingMap);

    QVariantMap GetSqlConnectionSettings() const;
    void SetSqlConnectionSettings(const QVariantMap &GetSqlConnectionSettings);

signals:
    void NewSettingAdded();

private:

    QMap<QString, ModelStruct> m_modelMapNew;
    QMap<QString, ModelSettings> m_settingMap;

    QVariantMap m_sqlConnectionSettings;


    //TODO Сделать сохранение класса в файл



};

#endif // DATACLASS_HPP
