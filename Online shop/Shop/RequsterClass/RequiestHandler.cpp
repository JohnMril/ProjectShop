#include "RequiestHandler.hpp"
#include "ui_RawDataHandler.h"

RequstClassHandler::RequstClassHandler(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RawDataHandler)
{
    m_pathToDir = QDir::currentPath()+"/rawData/";
    ui->setupUi(this);
}

RequstClassHandler::~RequstClassHandler()
{
    delete ui;
}

void RequstClassHandler::on_pushButtonGetAll_clicked()
{

}

void RequstClassHandler::FillWidgets()
{
    m_gridList = new QGridLayout(ui->siteList);
    ui->siteList->setLayout(m_gridList);

    RequestClass* tmpWidget;
    tmpWidget = new RequestClass;
    m_mapSubWidgets.insert(API::LANIT, tmpWidget);

    tmpWidget->SetApiEnum(API::LANIT);
    tmpWidget->SetSiteName("Lanit");
    tmpWidget->SetPathToFileExe(m_pathToDir+"Lanit.exe");


}

void RequstClassHandler::GetAllData()
{

}
