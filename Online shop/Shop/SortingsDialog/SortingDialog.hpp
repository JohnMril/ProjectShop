#ifndef SORTINGDIALOG_HPP
#define SORTINGDIALOG_HPP

#include <QDialog>
#include <QSortFilterProxyModel>

namespace Ui {
class SortingDialog;
}

class SortingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SortingDialog(QWidget *parent = nullptr);
    ~SortingDialog();



    void SetProxyModel(QSortFilterProxyModel *proxyModel);

private slots:
    void filterRegExpChanged();
    void filterColumnChanged();
    void sortChanged();


private:

    void FillColumnBox();
    QStringList m_columnList;

    QSortFilterProxyModel* m_proxyModel = nullptr;

    Ui::SortingDialog *ui;
};

#endif // SORTINGDIALOG_HPP
