#ifndef MODELVIEWDIALOG_HPP
#define MODELVIEWDIALOG_HPP

#include <QDialog>

#include <QStandardItemModel>
#include "Common/ModelStruct.hpp"
#include "ViewEditorDialog/ViewEditorDialog.hpp"
#include "ModelHandler.hpp"


namespace Ui {
class ModelViewDialog;
}

class ModelViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModelViewDialog(QStandardItemModel *itemModel, QWidget *parent = nullptr);
    ~ModelViewDialog();

    void closeEvent(QCloseEvent *) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ModelViewDialog *ui;

    ViewEditorDialog* m_viewEditor = nullptr;

    QStandardItemModel *m_itemModel;


};

#endif // MODELVIEWDIALOG_HPP
