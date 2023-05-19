#ifndef VIEWEDITORDIALOG_HPP
#define VIEWEDITORDIALOG_HPP

#include <QDialog>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QTableView>

#include "ViewSelectorWidgetForm.hpp"

namespace Ui {
class ViewEditorDialog;
}

class ViewEditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewEditorDialog(QTableView* view, QWidget *parent = nullptr);
    ~ViewEditorDialog();

private slots:
    void on_selectorPushButton_clicked();

private:

    void FillLayout();

    void HideShowColumn(int column);

    QTableView* m_view;

    QVector<ViewSelectorWidgetForm*> m_elementVec;

    Ui::ViewEditorDialog *ui;
};

#endif // VIEWEDITORDIALOG_HPP
