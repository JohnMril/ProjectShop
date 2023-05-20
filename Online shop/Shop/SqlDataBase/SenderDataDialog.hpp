#ifndef SENDERDATADIALOG_HPP
#define SENDERDATADIALOG_HPP

#include <QDialog>
#include <QDateTime>

#include "DataClass/DataClass.hpp"
#include "SqlElement.hpp"

namespace Ui {
class SenderDataDialog;
}

class SenderDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SenderDataDialog(DataClass* dataClass, QString modelStructName, QWidget *parent = nullptr);
    ~SenderDataDialog();

signals:
    void SetingsHasCreated(QString shopName);

private slots:

    void on_sendPushButton_clicked();

private:

    void FillWidgetByElements();

    DataClass* m_dataClass;
    QString m_modelStructName;
    QVector<SqlElement*> m_elementVec;

    Ui::SenderDataDialog *ui;
};

#endif // SENDERDATADIALOG_HPP
