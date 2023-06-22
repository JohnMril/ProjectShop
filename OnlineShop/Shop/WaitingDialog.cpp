#include "WaitingDialog.hpp"
#include "ui_WaitingDialog.h"

WaitingDialog::WaitingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingDialog)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &WaitingDialog::AtTime);
    m_timer->start(1000);
}

WaitingDialog::~WaitingDialog()
{
    delete ui;
}

void WaitingDialog::SwitchTimer(bool state)
{
    if(state)
    {
        StartTimer();
    }
    else
    {
        StartTimer();
    }
}

void WaitingDialog::StartTimer()
{
    m_currentTime = 0;
    this->show();
}

void WaitingDialog::StopTimer()
{
    this->hide();
}

void WaitingDialog::AtTime()
{
    m_currentTime++;

    QString currentTime;

    int minute = m_currentTime/60;

    if(minute > 0)
    {
        currentTime = QString::number(minute)+ "h.";
    }

    currentTime += QString::number(m_currentTime%60)+ "sec.";
    ui->labelTitle->setText(currentTime);
}
