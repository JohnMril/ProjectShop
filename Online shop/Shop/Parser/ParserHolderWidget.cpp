#include "ParserHolderWidget.hpp"

ParserHolderWidget::ParserHolderWidget(QWidget *parent) : QWidget(parent)
{

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

    m_parserDialog = new ParsingDialog(m_parser.GetModelStruct(),this);
    connect(m_parserDialog, &ParsingDialog::okIsClicked, this, &ParserHolderWidget::DialogSuccess);
    m_parserDialog->show();

}



QString ParserHolderWidget::EmitFileFinder()
{
    //TODO запоминать предыдущий путь.


    QString filter = "All File (*.*);; Text File (*.txt);; XML File (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open file", "C://",filter);

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



void ParserHolderWidget::DialogSuccess()
{
    m_dataClass->AddModelPair(m_parserDialog->GetModelStruct(), m_parserDialog->GetSettings());

    m_parserDialog->close();

    emit NewModelStructHasCreated();
}
