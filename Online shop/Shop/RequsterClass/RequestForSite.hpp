#ifndef GETSITERAWDATAWIDEGET_HPP
#define GETSITERAWDATAWIDEGET_HPP

#include <QWidget>
#include <QByteArray>
#include <QFile>
#include <QProcess>
#include <QDateTime>
#include <QDebug>

#include "../Common/EnumerationClass.hpp"



namespace Ui {
class GetSiteRawDataWideget;
}

class RequestClass : public QWidget
{
    Q_OBJECT

public:
    explicit RequestClass(QWidget *parent = nullptr);

    ~RequestClass();

    bool IsEnabled();
    void StartGettingData();

    QString GetDate();
    void SetPeriodTimeAccess(int periodTimeAccess);

    QString GetDateTime() const;

    QString GetSiteName() const;

    API GetApiEnum() const;
    void SetApiEnum(const API &GetApiEnum);

    void SetSiteName(const QString &siteName);
    void SetPathToFileExe(const QString &pathToFileExe);

signals:
    void dataAccepted(const int &);

private slots:
    void emitSignals(int exitCode, QProcess::ExitStatus exitStatus);

private:

    bool IsTimeAccess();

    Ui::GetSiteRawDataWideget *ui;

    QProcess* m_currentProcess;

    QByteArray m_rawData;
    QString m_siteName;
    QString m_dateTime;
    QString m_date;
    QString m_pathToFileExe;

    /**
     * @brief m_periodTimeAccess Период получения данных в минутах
     */
    int m_periodTimeAccess;
    API m_apiEnum;


};

#endif // GETSITERAWDATAWIDEGET_HPP
