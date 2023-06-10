#include "ViewEditorDialog.hpp"
#include "ui_ViewEditorDialog.h"

ViewEditorDialog::ViewEditorDialog(QTableView *view, QWidget *parent) :
    QDialog(parent),
    m_view(view),
    ui(new Ui::ViewEditorDialog)
{
    ui->setupUi(this);

    FillLayout();

}

ViewEditorDialog::~ViewEditorDialog()
{
    delete ui;
}



void ViewEditorDialog::FillLayout()
{
    QAbstractItemModel* model = m_view->model();

    for(int column = 0; column < model->columnCount(); column++)
    {
        bool state = !m_view->isColumnHidden(column);
        ViewSelectorWidgetForm* tmpElement = new ViewSelectorWidgetForm(column, model->headerData(column, Qt::Horizontal).toString(), state, this);
        connect(tmpElement, &ViewSelectorWidgetForm::checkBoxClicked, this, &ViewEditorDialog::HideShowColumn);
        m_elementVec.push_back(tmpElement);
        ui->verticalLayout_2->addWidget(tmpElement);
    }
}




void ViewEditorDialog::HideShowColumn(int column)
{
    if(m_elementVec.at(column)->isChecked())
    {
        m_view->showColumn(column);
    }
    else
    {
        m_view->hideColumn(column);
    }
}

void ViewEditorDialog::on_selectorPushButton_clicked()
{
    for ( auto element : m_elementVec)
    {
        element->SetChecked(true);
    }
}
