#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QString serverAdres ="(local)" ;
    QString dataBaseName = "QTBD";
    QString userName = "sa";
    QString password = "1234";
    m_sqlDataBase.MakeConection(serverAdres, dataBaseName, userName, password);

    m_selectorFileDialog = new SelecterParsingFilesDialog(this);
    m_selectorFileDialog->hide();

    m_parserHolder = new ParserHolderWidget(this);
    m_parserHolder->SetDataClass(&m_dataClass);
    m_modelHandler.SetDataClass(&m_dataClass);

    ui->modelsView->setModel(m_modelHandler.GetPlacesModels());

    connect(m_parserHolder, &ParserHolderWidget::NewModelStructHasCreated, &m_modelHandler, &ModelHandler::CreateNewModelFromDataClass);

    connect(&m_modelHandler, &ModelHandler::CreatedNewModel, this, &MainWindow::AddNewModelViewElement);

    connect(m_selectorFileDialog, &SelecterParsingFilesDialog::sourceDataSelected, m_parserHolder, &ParserHolderWidget::DataLoaded);
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
//    if(m_viewEditorDialog != nullptr)
//    {
//        m_viewEditorDialog->close();
//        delete m_viewEditorDialog;
//    }


    if(m_modelHandler.GetMapOfProxyModels().contains(arg1))
    {
        m_currenttProxyModel = m_modelHandler.GetMapOfProxyModels().value(arg1);
        ui->currentModelView->setModel(m_modelHandler.GetMapOfProxyModels().value(arg1));
    }
}



void MainWindow::AddNewModelViewElement()
{
    ui->comboBox->setModel(m_modelHandler.GetPlacesModels());

//   ModelStruct* tmpModel =  m_dataClass.GetLastModelStruct();
//   bool state = true;
//   QVector<QVariantList> tmpVec =  m_dataClass.GetDataListToSql(tmpModel->shop, tmpModel->date, state);

//   if(state)
//   {
//       m_sqlDataBase.InsertItems(tmpVec);
//   }
}



void MainWindow::on_actionAdd_row_2_triggered()
{
    if(m_currenttProxyModel)
        m_currenttProxyModel->insertRow(ui->currentModelView->selectionModel()->currentIndex().row());
}



void MainWindow::on_actionRemove_row_2_triggered()
{
    if(m_currenttProxyModel)
        m_currenttProxyModel->removeRow(ui->currentModelView->selectionModel()->currentIndex().row());
}



void MainWindow::on_actionSort_column_triggered()
{

    if(m_currenttProxyModel)
        m_currenttProxyModel->sort( ui->currentModelView->selectionModel()->currentIndex().column()
                                    , Qt::AscendingOrder);

}



void MainWindow::on_actionFinding_by_name_triggered()
{
    if(!m_sortingDialog)
    {
        m_sortingDialog = new SortingDialog(this);
        m_sortingDialog->SetProxyModel(m_currenttProxyModel);
        m_sortingDialog->show();

    }
}



void MainWindow::on_pushButton_2_clicked()
{
    m_parserHolder->DataLoaded(API::LANIT);
}



void MainWindow::on_pushButton_3_clicked()
{
    m_selectorFileDialog->show();
}



void MainWindow::on_editViewPushButton_clicked()
{
    //TODO сделать сообщение что модели нет
    if(ui->currentModelView->model() == nullptr)
    {
        return;
    }
    m_viewEditorDialog = new ViewEditorDialog(ui->currentModelView, this);
    m_viewEditorDialog->show();
}
