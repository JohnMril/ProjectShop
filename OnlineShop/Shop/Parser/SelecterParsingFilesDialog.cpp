#include "SelecterParsingFilesDialog.hpp"
#include "ui_SelecterParsingFilesDialog.h"

SelecterParsingFilesDialog::SelecterParsingFilesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelecterParsingFilesDialog)
{
    ui->setupUi(this);

    m_eventLoop = new QEventLoop(this);

    m_requstHandler = new RequestClassHandler(this);
    m_requstHandler->hide();

    m_currentDir.setPath(QDir::currentPath());
    m_currentDir.cdUp();
    if(!m_currentDir.cd("rawData"))
    {
        qDebug() << "cant found rawData dir";
    }
    m_pathToDir = m_currentDir.path();

    m_gridLayout = new QGridLayout(ui->filesToLoad);

    m_enumMap.insert(API::LANIT, "LanitProducts.txt");
    m_enumMap.insert(API::ASBIS, "asbisProducts.txt");
    m_enumMap.insert(API::MARVEL, "MarvelProducts.txt");
    m_enumMap.insert(API::RRC,"RRCProducts.txt");
    m_enumMap.insert(API::INLINE,"InlineProducts.txt");
    m_enumMap.insert(API::PRONET,"PronetProducts.txt");
    m_enumMap.insert(API::TRADEONLINE, "TradeOnlineProducts.txt");
    m_enumMap.insert(API::OCS, "OcsProducts.txt");
    m_enumMap.insert(API::MICS, "MicsProducts.txt");
    m_enumMap.insert(API::NETLAB,  "NetLabProducts.txt");
    m_enumMap.insert(API::ELKO,  "ElkoProducts.txt");
    m_enumMap.insert(API::SUPERWAVE, "SuperWaveProducts.txt");
    m_enumMap.insert(API::RESOURCEMEDIA, "ResourceMediaProducts.txt");




    on_pushButton_clicked();
}



SelecterParsingFilesDialog::~SelecterParsingFilesDialog()
{
    delete ui;
}



void SelecterParsingFilesDialog::acceptSignal(QString text)
{
    qDebug() <<"fileName "<< text;

    if(m_enumMap.values().contains(text))
    {
        emit sourceDataSelected(m_enumMap.key(text));
    }

}



void SelecterParsingFilesDialog::LoadAllData()
{
    m_minute = 0;
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SelecterParsingFilesDialog::timeOutTimer);
    m_timer->start(60*1000);

    QFileInfoList fileList = m_currentDir.entryInfoList();
    for(auto fileInfo : fileList)
    {
        if(!fileInfo.fileName().contains("Products.txt"))
        {
            fileList.removeOne(fileInfo);
        }
    }
    for(auto fileInfo : fileList)
    {
        if(!fileInfo.fileName().contains("Products.txt"))
        {
            fileList.removeOne(fileInfo);
        }
    }

    m_requstHandler->GetAllData();

    bool switchKey = true;

    while (switchKey)
    {
        bool state = true;
        m_currentDir.setPath(m_pathToDir);
        QFileInfoList tmpfileList = m_currentDir.entryInfoList();
        for(auto fileInfo : tmpfileList)
        {
            if(!fileInfo.fileName().contains("Products.txt"))
            {
                tmpfileList.removeOne(fileInfo);
            }
        }
        for(auto fileInfo : tmpfileList)
        {
            if(!fileInfo.fileName().contains("Products.txt"))
            {
                tmpfileList.removeOne(fileInfo);
            }
        }

        for(auto file0 : tmpfileList)
        {
            for(auto file1 : fileList)
            {
                if(file0.fileName() == file1.fileName())
                {
                    if(file0.lastModified().toString() == file1.lastModified().toString())
                    {
                        state = false;
                    }
                }
            }
        }
        m_eventLoop->processEvents();
        if(state || (m_minute >12))
        {
            switchKey = false;
        }
    }

    on_pushButton_clicked();
    for (auto widget : m_fileSelectorVec)
    {
        widget->on_pushButton_clicked();
    }
    emit allDataLoaded();
    qDebug() << "AllDataLoaded";
    m_timer->stop();
    m_timer->deleteLater();
    delete m_timer;
}



void SelecterParsingFilesDialog::on_pushButton_clicked()
{
    for (auto widget : m_fileSelectorVec)
    {
        delete widget;
    }
    m_fileSelectorVec.clear();

    m_currentDir.setPath(m_pathToDir);
    m_currentFileList = m_currentDir.entryInfoList();

    FileSelector* tmpWidget;
    for (auto file : m_currentFileList)
    {
        if(file.fileName().contains("Products.txt"))
        {
            tmpWidget = new FileSelector(file, this);
            connect(tmpWidget, &FileSelector::fileSelected, this, &SelecterParsingFilesDialog::acceptSignal);

            m_gridLayout->addWidget(tmpWidget);
            m_fileSelectorVec.push_back(tmpWidget);
        }
    }
}




void SelecterParsingFilesDialog::on_loadPushButton_clicked()
{
    m_requstHandler->show();
}



void SelecterParsingFilesDialog::timeOutTimer()
{
    m_minute++;
}
