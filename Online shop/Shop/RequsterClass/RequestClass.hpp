#ifndef REQUESTCLASS_HPP
#define REQUESTCLASS_HPP

#include <QWidget>
#include <QWidget>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QDateTime>
#include <QDebug>
#include <QTimer>


namespace Ui {
class RequestClass;
}

class RequestClass : public QWidget
{
    Q_OBJECT

public:
    explicit RequestClass(QFileInfo fileInfo, QWidget *parent = nullptr);
    ~RequestClass();

    void StartGettingData();

    void SetPeriodTimeAccess(int periodTimeAccess);

private:

    void TimerSlot();

    Ui::RequestClass *ui;

    QProcess* m_currentProcess;

    QString m_pathToFileExe;

    QTimer* m_timer;
    int     m_timerCounter = 0;
    /**
     * @brief m_periodTimeAccess Период получения данных в минутах
     */
    int m_periodTimeAccess;

    QFileInfo m_fileInfo;
};

#endif // REQUESTCLASS_HPP
