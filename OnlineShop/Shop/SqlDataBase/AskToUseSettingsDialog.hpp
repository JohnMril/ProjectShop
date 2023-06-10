#ifndef ASKTOUSESETTINGSDIALOG_HPP
#define ASKTOUSESETTINGSDIALOG_HPP

#include <QDialog>
#include <QPushButton>

namespace Ui {
class AskToUseSettingsDialog;
}

class AskToUseSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AskToUseSettingsDialog(QString shopName, QString date, QWidget *parent = nullptr);
    ~AskToUseSettingsDialog();

signals:
    void ApplyPressed(QString);
    void EditPressed (QString);

private slots:
    void on_ApplyPushButton_clicked();

    void on_EditPushButton_clicked();

private:

    QString m_shopName;
    Ui::AskToUseSettingsDialog *ui;
};

#endif // ASKTOUSESETTINGSDIALOG_HPP
