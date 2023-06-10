#ifndef CHOSESETTINGSDIALOG_HPP
#define CHOSESETTINGSDIALOG_HPP

#include <QDialog>
#include "DataClass/DataClass.hpp"
#include "Common/ModelStruct.hpp"

namespace Ui {
class ChoseSettingsDialog;
}

class ChoseSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoseSettingsDialog(QVector<ModelSettings> &settings ,  QWidget *parent = nullptr);
    ~ChoseSettingsDialog();

    QVector<ModelSettings> GetVecSettings() const;

signals:
    void ApplyClicked(const int&);
    void EdditClicked(const int&);

private slots:
    void on_ApplyPushButton_clicked();

    void on_EdditPushButton_clicked();

private:

    QVector<ModelSettings> m_vecSettings;
    QStringList m_listOfSettings;
    int m_chosenIndex;

    Ui::ChoseSettingsDialog *ui;
};

#endif // CHOSESETTINGSDIALOG_HPP
