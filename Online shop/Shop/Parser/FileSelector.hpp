#ifndef FILESELECTOR_HPP
#define FILESELECTOR_HPP

#include <QWidget>
#include <QFileInfo>
#include <QDateTime>

namespace Ui {
class FileSelector;
}

class FileSelector : public QWidget
{
    Q_OBJECT

public:
    explicit FileSelector(QFileInfo fileInfo,QWidget *parent = nullptr);
    ~FileSelector();

signals:
    void fileSelected(QString);

private slots:
    void on_pushButton_clicked();


private:
    Ui::FileSelector *ui;

    QFileInfo m_fileInfo;
};

#endif // FILESELECTOR_HPP
