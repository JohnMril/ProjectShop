#ifndef PARSINGDIALOG_HPP
#define PARSINGDIALOG_HPP

#include <QDialog>

namespace Ui {
class ParsingDialog;
}

class ParsingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParsingDialog(QWidget *parent = nullptr);
    ~ParsingDialog();

private:
    Ui::ParsingDialog *ui;
};

#endif // PARSINGDIALOG_HPP
