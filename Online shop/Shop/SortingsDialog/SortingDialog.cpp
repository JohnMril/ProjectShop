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



void SortingDialog::filterRegExpChanged()
{

}



void SortingDialog::filterColumnChanged()
{

}



void SortingDialog::sortChanged()
{

}



void SortingDialog::FillColumnBox()
{
    m_columnList.clear();
    for(int column = 0; column < m_proxyModel->columnCount(); ++column)
    {
        m_columnList.append(m_proxyModel->headerData(column, Qt::Orientation::Horizontal, Qt::DisplayRole).toString());

    }

    ui->columnComboBox->addItems(m_columnList);
}



void SortingDialog::SetProxyModel(QSortFilterProxyModel *proxyModel)
{
    m_proxyModel = proxyModel;
    FillColumnBox();
}

