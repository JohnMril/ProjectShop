#include "RequestForSite.hpp"
#include "ui_GetSiteRawDataWideget.h"

RequestClass::RequestClass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GetSiteRawDataWideget)
{
    ui->setupUi(this);
}



RequestClass::~RequestClass()
{
    delete ui;
}



bool RequestClass::IsEnabled()
{
    return ui->radioButton->isChecked();
}



void RequestClass::StartGettingData()
{
    m_currentProcess = new QProcess(this);

    connect(m_currentProcess, SIGNAL(finished(int , QProcess::ExitStatus )),
            this, SLOT(on_cameraControlExit(int , QProcess::ExitStatus )));

    m_currentProcess->start(m_pathToFileExe);
}



QString RequestClass::GetDate()
{
    return m_date;
}



void RequestClass::SetPeriodTimeAccess(int periodTimeAccess)
{
    m_periodTimeAccess = periodTimeAccess;
}



bool RequestClass::IsTimeAccess()
{
    //FIXME Сделать проверку на последнюю выдачу данных если есть ограничения
    return true;
}

void RequestClass::SetPathToFileExe(const QString &pathToFileExe)
{
    m_pathToFileExe = pathToFileExe;
}

void RequestClass::emitSignals(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "int exitCode" << exitCode;
    qDebug() << "QProcess::ExitStatus exitStatus" << exitStatus;

    if(exitStatus == QProcess::NormalExit)
    {
        emit dataAccepted(m_apiEnum);
    }
}

void RequestClass::SetSiteName(const QString &siteName)
{
    m_siteName = siteName;
}



API RequestClass::GetApiEnum() const
{
    return m_apiEnum;
}



void RequestClass::SetApiEnum(const API &apiEnum)
{
    m_apiEnum = apiEnum;
}



QString RequestClass::GetSiteName() const
{
    return m_siteName;
}



QString RequestClass::GetDateTime() const
{
    return m_dateTime;
}

