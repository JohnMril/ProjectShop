#include "LogDialog.hpp"
#include "ui_LogDialog.h"

LogDialog::LogDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogDialog)
{
    ui->setupUi(this);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &LogDialog::TimeOut);
    m_timer->start(1000);
    this->setWindowTitle("Логгирование");
    this->hide();
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::TextChange(QString text)
{
    ui->labelText->setText(text);
    m_seconds = 0;
    this->show();
}

void LogDialog::Finished()
{
    this->hide();
}

void LogDialog::TimeOut()
{
    m_seconds++;
    ui->labelTimer->setText(SecondsToTime());
}

void LogDialog::closeEvent(QCloseEvent *event)
{
    this->hide();
}

QString LogDialog::SecondsToTime()
{

    QString sec = QString::number(m_seconds%60);
    QString minutes = QString::number(m_seconds / 60);

    return  minutes+":"+sec;
}
