#ifndef SORTINGDIALOG_HPP
#define SORTINGDIALOG_HPP

#include <QDialog>

namespace Ui {
class SortingDialog;
}

class SortingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SortingDialog(QWidget *parent = nullptr);
    ~SortingDialog();

private:
    Ui::SortingDialog *ui;
};

#endif // SORTINGDIALOG_HPP
