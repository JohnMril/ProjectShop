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
    m_timer = new  QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &RequestClass::TimerSlot);
    m_timer->start();

//    connect(m_currentProcess, SIGNAL(finished(int , QProcess::ExitStatus )),
//            this, SLOT(emitSignals(int , QProcess::ExitStatus )));



//    m_currentProcess->start(m_pathToFileExe);
    m_currentProcess->setProgram(m_pathToFileExe);
    m_currentProcess->setStandardOutputFile( QProcess::nullDevice() );
    m_currentProcess->setStandardErrorFile( QProcess::nullDevice() );

    m_currentProcess->startDetached();
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

void RequestClass::SetPathSourceFile(const QString &pathSourceFile)
{
    m_pathSourceFile = pathSourceFile;
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

void RequestClass::TimerSlot()
{
    m_timerCounter++;
    //TODO переделать под минуты и секунды
    ui->label_2->setText("sec:"+QString::number(m_timerCounter));

    QFile file(m_pathSourceFile);
    QFileInfo fileInfo(file);
    QDateTime dateTime = fileInfo.lastModified();
    QString tmpDate = dateTime.toString();

    qDebug() << "Timer " << m_pathSourceFile;

    if(m_lastGettedDate != tmpDate)
    {
        m_lastGettedDate = tmpDate;

        ui->label_2->setText("Data has been added after"+QString::number(m_timerCounter)+ "sec");
        emit dataAccepted(m_apiEnum);
    }

    if(m_timerCounter > (60*5))
    {
        m_timerCounter = 0;
        m_timer->stop();
        delete m_timer;
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

