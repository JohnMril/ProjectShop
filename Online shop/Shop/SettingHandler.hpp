#ifndef SETTINGHANDLER_HPP
#define SETTINGHANDLER_HPP


#include <QObject>
#include <QMap>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonObject>

#include <QFile>
#include <QDebug>
#include <QByteArray>

#include "DataClass/DataClass.hpp"//;




class SettingHandler : public QObject
{
    Q_OBJECT
public:
    explicit SettingHandler(DataClass* dataClass, QObject *parent = nullptr);

    bool SettingSave();

    bool SettingDownload();

signals:

private:

    DataClass* m_dataClass;

    QDir m_settingDir;

    QMap<QString, ModelSettings> m_settingMap;

};

#endif // SETTINGHANDLER_HPP
