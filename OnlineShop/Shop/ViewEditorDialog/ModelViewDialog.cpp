#include "ModelViewDialog.hpp"
#include "ui_ModelViewDialog.h"

ModelViewDialog::ModelViewDialog(QStandardItemModel *itemModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelViewDialog),
    m_itemModel(itemModel)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->tableView->setModel(itemModel);
}

ModelViewDialog::~ModelViewDialog()
{    
    delete m_itemModel;
    delete ui;
}

void ModelViewDialog::closeEvent(QCloseEvent *)
{
    //FIXME сделать удаление
}


void ModelViewDialog::on_pushButton_clicked()
{
    m_viewEditor = new ViewEditorDialog(ui->tableView, this);
    m_viewEditor->show();
}
