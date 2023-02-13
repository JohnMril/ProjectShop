#include "SortingDialog.hpp"
#include "ui_SortingDialog.h"

SortingDialog::SortingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SortingDialog)
{
    ui->setupUi(this);
}

SortingDialog::~SortingDialog()
{
    delete ui;
}
