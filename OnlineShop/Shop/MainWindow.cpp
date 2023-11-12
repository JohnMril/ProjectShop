#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_logDialog = new LogDialog();

    m_settingHandler = new SettingHandler(&m_dataClass, this);    
    m_settingHandler->SettingDownload();

    m_sqlDataBaseHandler = new SqlDatabaseHandler(&m_dataClass, this);
    m_sqlAuthDialog = new AuthorizationDialog(m_sqlDataBaseHandler, this);
    m_sqlDataBaseHandler->hide();

    connect(m_sqlDataBaseHandler, &SqlDatabaseHandler::NeedToConnect, this, &MainWindow::EmitAuthSql);
    connect(m_sqlDataBaseHandler, &SqlDatabaseHandler::ShowMainWindow, this, &MainWindow::ShowMainWindow);
    connect(m_sqlDataBaseHandler, &SqlDatabaseHandler::Started, m_logDialog, &LogDialog::TextChange);
    connect(m_sqlDataBaseHandler, &SqlDatabaseHandler::Finished, m_logDialog, &LogDialog::Finished);


    m_selectorFileDialog = new SelecterParsingFilesDialog(this);
    m_selectorFileDialog->hide();

    m_parserHolder = new ParserHolderWidget(this);
    m_parserHolder->SetDataClass(&m_dataClass);
    m_modelHandler.SetDataClass(&m_dataClass);

    ui->modelsView->setModel(m_modelHandler.GetPlacesModels());
    ui->modelsView->resizeColumnsToContents();

    connect(&m_modelHandler, &ModelHandler::CreatedNewModel, this, &MainWindow::AddNewModelViewElement);

    connect(m_selectorFileDialog, &SelecterParsingFilesDialog::sourceDataSelected, m_parserHolder, &ParserHolderWidget::DataLoaded);
    connect(m_selectorFileDialog, &SelecterParsingFilesDialog::allDataLoaded, m_sqlDataBaseHandler, &SqlDatabaseHandler::SendAllDataToSqlServer);

    connect(m_parserHolder, &ParserHolderWidget::NewModelLoaded, &m_modelHandler, &ModelHandler::CreateModelByString);



    //setting
    connect(&m_dataClass, &DataClass::NewSettingAdded, m_settingHandler, &SettingHandler::SettingSave);


    m_sqlDataBaseHandler->MakeConnection();


    this->resize(525, 350);

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowMainWindow()
{
    this->show();
}



void MainWindow::AddNewModelViewElement(const QString& modelName)
{
//    ui->comboBox->setModel(m_modelHandler.GetPlacesModels());

//    QMap<QString, QSortFilterProxyModel*> tmpMap = m_modelHandler.GetMapOfProxyModels();
//    if(tmpMap.contains(modelName))
        if(true)
    {
//        ui->currentModelView->setModel(tmpMap.value(modelName));

        PushButtonSender* button = new PushButtonSender(modelName, this);
        connect(button, &PushButtonSender::Clicked, this, &MainWindow::PreapareToSendData);
        ui->modelsView->setIndexWidget(m_modelHandler.GetIndexOfPlacesModelByName(modelName), button);

        PushButtonSender* button0 = new PushButtonSender(modelName, this);
        connect(button0, &PushButtonSender::Clicked, this, &MainWindow::EmitModelViewDialog);
        ui->modelsView->setIndexWidget(m_modelHandler.GetIndexOfPlacesModelByName(modelName, 3), button0);


        ui->modelsView->resizeColumnsToContents();


    }
}

void MainWindow::EmitAuthSql()
{
    m_sqlAuthDialog->show();
}



void MainWindow::on_pushButton_3_clicked()
{
    m_selectorFileDialog->show();
}



void MainWindow::EmitModelViewDialog(QString modelName)
{

    QStandardItemModel* model = m_modelHandler.CreateTmpMOdel(modelName);
    if(model != nullptr)
    {

        m_viewDialog = new ModelViewDialog(model, this);
        m_viewDialog->show();
    }
}



void MainWindow::PreapareToSendData(QString name)
{
    qDebug()<<"Pressed" <<name;
    m_sqlDataBaseHandler->PrepareToSend(name);
}



void MainWindow::on_loadAllButton_clicked()
{
    if(!m_sqlDataBaseHandler->isConnected())
    {
        EmitAuthSql();
    }
    else
    {
        this->hide();
        m_logDialog->TextChange("Происходит скачка файлов по API (приблизительно 12 минут)");
        m_selectorFileDialog->LoadAllData();

    }
}

void MainWindow::on_sqlScript_clicked()
{
    if(!m_sqlDataBaseHandler->isConnected())
    {
        EmitAuthSql();
    }
    else
    {

        this->hide();
        m_sqlDataBaseHandler->EmitSqlRecount();
    }
}
