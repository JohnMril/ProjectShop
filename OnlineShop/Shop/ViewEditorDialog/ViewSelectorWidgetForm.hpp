#ifndef VIEWSELECTORWIDGETFORM_HPP
#define VIEWSELECTORWIDGETFORM_HPP

#include <QWidget>

namespace Ui {
class ViewSelectorWidgetForm;
}

class ViewSelectorWidgetForm : public QWidget
{
    Q_OBJECT

public:
    explicit ViewSelectorWidgetForm(int number, QString keyName, bool state = true, QWidget *parent = nullptr);
    ~ViewSelectorWidgetForm();

    bool isChecked();

    void SetChecked(bool state);

signals:
    void checkBoxClicked(int);

private:

    void EmitSignal();

    int m_number;
    QString m_keyName;

    Ui::ViewSelectorWidgetForm *ui;
};

#endif // VIEWSELECTORWIDGETFORM_HPP
