#include "RequiestHandler.hpp"
#include "ui_RawDataHandler.h"

RequestClassHandler::RequestClassHandler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RawDataHandler)
{
    m_pathToDir = QDir::currentPath()+"/rawData/";
    ui->setupUi(this);

    FillWidgets();
}

RequestClassHandler::~RequestClassHandler()
{
    delete ui;
}

void RequestClassHandler::on_pushButtonGetAll_clicked()
{
    GetAllData();
}

void RequestClassHandler::emitSignal(const int &enumApi)
{
    qDebug() << "RequstClassHandler accepted " << enumApi;
    emit DataAccepted(enumApi);
}

void RequestClassHandler::FillWidgets()
{
    m_gridList = new QGridLayout(ui->siteList);
    ui->siteList->setLayout(m_gridList);

    RequestClass* tmpWidget;
    tmpWidget = new RequestClass;
    connect(tmpWidget, &RequestClass::dataAccepted, this, &RequestClassHandler::emitSignal);
    m_mapSubWidgets.insert(API::LANIT, tmpWidget);

    tmpWidget->SetApiEnum(API::LANIT);
    tmpWidget->SetSiteName("Lanit");
    tmpWidget->SetPathToFileExe(m_pathToDir+"startLanit.bat");
    tmpWidget->SetPathSourceFile(m_pathToDir+"LanitProducts.txt");

    m_gridList->addWidget(tmpWidget);


}

void RequestClassHandler::GetAllData()
{
     for (auto widget : m_mapSubWidgets)
     {
         if(widget->IsEnabled())
         {
            widget->StartGettingData();
         }
     }

//     this->hide();
}
