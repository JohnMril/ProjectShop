#ifndef SELECTEDPARSERELEMENTWIDGET_HPP
#define SELECTEDPARSERELEMENTWIDGET_HPP

#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QGridLayout>


#include "../Common/EnumerationClass.hpp"
#include "../Common/ModelStruct.hpp"


class SelectedParserElementWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectedParserElementWidget(QString key, int number , QWidget *parent = nullptr,
                                         ElementsType type = ElementsType::UNKNOWN_TYPE,
                                         bool state = false, QString valueStr = "");

    ElementSettings GetSource();

private:

    void CreateWidgetBySource();
    void SaveToSource();

    void SwitchCheckBox();

    QLabel* m_keyNameLabel;
    QSpinBox* m_spinBox;
    QLineEdit* m_lineEdit;
    QCheckBox* m_checkBox;
    QComboBox* m_typeBox;

    QGridLayout* m_gridLayout;

    QStringList m_typeList;


    ElementSettings m_source;

};

#endif // SELECTEDPARSERELEMENTWIDGET_HPP
