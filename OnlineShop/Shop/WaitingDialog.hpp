#ifndef WAITINGDIALOG_HPP
#define WAITINGDIALOG_HPP

#include <QDialog>
#include <QTimer>

namespace Ui {
class WaitingDialog;
}

class WaitingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingDialog(QWidget *parent = nullptr);
    ~WaitingDialog();



public slots:
    void SwitchTimer(bool state);

    void StartTimer();

    void StopTimer();

private slots:
    void AtTime();
private:

    int m_currentTime;

    QTimer* m_timer;

    Ui::WaitingDialog *ui;
};

#endif // WAITINGDIALOG_HPP
