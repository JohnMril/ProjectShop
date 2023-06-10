#include "RequestClass.hpp"
#include "ui_RequestClass.h"

RequestClass::RequestClass(QFileInfo fileInfo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RequestClass),
    m_pathToFileExe(fileInfo.filePath()),
    m_fileInfo(fileInfo)
{
    ui->setupUi(this);
    ui->labelDate->setText("");
    ui->labelSite->setText(m_fileInfo.fileName());
}

RequestClass::~RequestClass()
{
    delete ui;
}



void RequestClass::StartGettingData()
{
     ui->labelDate->setText(QTime::currentTime().toString());
    //TODO сделать ограничение по времени
    m_currentProcess = new QProcess(this);
    m_timer = new  QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &RequestClass::TimerSlot);
    m_timer->start();

    m_currentProcess->setProgram(m_pathToFileExe);
    m_currentProcess->setStandardOutputFile( QProcess::nullDevice() );
    m_currentProcess->setStandardErrorFile( QProcess::nullDevice() );

    m_currentProcess->startDetached();
}

void RequestClass::SetPeriodTimeAccess(int periodTimeAccess)
{
    m_periodTimeAccess = periodTimeAccess;
}



void RequestClass::TimerSlot()
{
    m_timerCounter++;
    //TODO переделать под минуты и секунды

    if(m_timerCounter > (60*5))
    {
        m_timerCounter = 0;
        m_timer->stop();
        delete m_timer;
    }
}

void RequestClass::on_getPushButton_clicked()
{
    StartGettingData();
}
