#ifndef SQLELEMENT_HPP
#define SQLELEMENT_HPP

#include <QWidget>
#include <QPair>
#include <QComboBox>

#include "Common/EnumerationClass.hpp"

namespace Ui {
class SqlElement;
}

class SqlElement : public QWidget
{
    Q_OBJECT

public:
    explicit SqlElement(QString GetKeyName, ElementsType GetType, QWidget *parent = nullptr);
    ~SqlElement();



    QString GetKeyName() const;

    ElementsType GetType() const;

private slots:
    void on_enumComboBox_currentIndexChanged(int index);

private:

    QString m_keyName;
    ElementsType m_type;

    Ui::SqlElement *ui;
};

#endif // SQLELEMENT_HPP
