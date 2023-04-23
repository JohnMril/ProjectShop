#include "ParserHolderWidget.hpp"

ParserHolderWidget::ParserHolderWidget(QWidget *parent) : QWidget(parent)
{
    m_parserMap.insert(API::LANIT,new LanitParser("Lanit", "LanitProducts.txt", this));
}



void ParserHolderWidget::AddNewFile()
{
    QString pathString = EmitFileFinder();

    if(pathString.isNull())
    {
        return;
    }

    if (!ParseByFilePath(pathString))
    {
        CallErorrMessageBox("File can't be read!!!", "file error");
        return;
    }


    ChooseSettings();


}



QString ParserHolderWidget::EmitFileFinder()
{
    QString filter = "All File (*.*);; Text File (*.txt);; XML File (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", m_lastFilePath,filter);

    QStringList splitPath = file_name.split("/");
    splitPath.takeLast();
    m_lastFilePath.clear();
    for (auto elem : splitPath)
    {
        m_lastFilePath.append(elem);
        m_lastFilePath.append("/");
    }

    return file_name;
}



bool ParserHolderWidget::ParseByFilePath(QString path)
{
    //TODO Добавить парсинг в зависимости от типа файла.
    return m_parser.ParsingFileToModel(path);
}



void ParserHolderWidget::CallErorrMessageBox(QString text, QString title)
{
    //TODO переделать под messageBox

    qDebug() << text<< title;
}



void ParserHolderWidget::SetDataClass(DataClass *dataClass)
{
    m_dataClass = dataClass;
}



void ParserHolderWidget::DataLoaded(const int &apiEnum)
{
    API tmpApi = static_cast<API>(apiEnum);
    if(m_parserMap.contains(tmpApi))
    {
        if(m_parserMap.value(tmpApi)->VParsing())
        {
           m_lastModel = m_parserMap.value(tmpApi)->GetModelStruct();
           ChooseSettings();
        }

    }
}



void ParserHolderWidget::DialogSuccess()
{
    m_dataClass->AddModelPair(m_parserDialog->GetModelStruct(), m_parserDialog->GetSettings());

    m_parserDialog->close();

    emit NewModelStructHasCreated();
}



void ParserHolderWidget::ChooseSettings()
{

    QSet<int> foundedSettings = m_dataClass->FindForSettings(m_lastModel);

    if(foundedSettings.isEmpty())
    {
        m_parserDialog = new ParsingDialog(m_lastModel, this);

        connect(m_parserDialog, &ParsingDialog::okIsClicked, this, &ParserHolderWidget::DialogSuccess);
        m_parserDialog->show();
    }
    else
    {
        QVector<ModelSettings> modelSettings;
        QVector<ModelSettings> tmpModelSettings = m_dataClass->GetSettingsVec();
        for (auto index : foundedSettings)
        {
            modelSettings.append(tmpModelSettings.at(index));
        }

        m_chooseSettingsDialog = new ChoseSettingsDialog(modelSettings, this);
        connect(m_chooseSettingsDialog, &ChoseSettingsDialog::ApplyClicked, this, &ParserHolderWidget::SettingApply);
        connect(m_chooseSettingsDialog, &ChoseSettingsDialog::EdditClicked, this, &ParserHolderWidget::SettingEdit);
    }

}



void ParserHolderWidget::SettingApply(const int &index)
{
    m_dataClass->AddModelPair(m_lastModel, m_chooseSettingsDialog->GetVecSettings().at(index));

    m_chooseSettingsDialog->close();
    delete  m_chooseSettingsDialog;

    emit NewModelStructHasCreated();
}



void ParserHolderWidget::SettingEdit(const int &index)
{
    m_parserDialog = new ParsingDialog(m_chooseSettingsDialog->GetVecSettings().at(index), m_parser.GetLastModelStruct(), this);

    connect(m_parserDialog, &ParsingDialog::okIsClicked, this, &ParserHolderWidget::DialogSuccess);

    m_chooseSettingsDialog->close();
    delete  m_chooseSettingsDialog;

    m_parserDialog->show();
}
