#ifndef LOGDIALOG_HPP
#define LOGDIALOG_HPP

#include <QWidget>
#include <QTimer>

namespace Ui {
class LogDialog;
}

class LogDialog : public QWidget
{
    Q_OBJECT

public:
    explicit LogDialog(QWidget *parent = nullptr);
    ~LogDialog();

public slots:
    void TextChange(QString text);
    void Finished();

private slots:
    void TimeOut();

private:
    void closeEvent(QCloseEvent *event) override;
    QString SecondsToTime();
    Ui::LogDialog *ui;

    int m_seconds;
    QTimer* m_timer;


};

#endif // LOGDIALOG_HPP
