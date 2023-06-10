#ifndef PUSHBUTTONSENDER_HPP
#define PUSHBUTTONSENDER_HPP

#include <QWidget>
#include <QPushButton>

class PushButtonSender : public QPushButton
{
    Q_OBJECT
public:
    PushButtonSender(QString shopName,QWidget *parent = nullptr);

    QString shopName() const;
signals:
    void Clicked(QString);

private:
    void ButtonClicked();

    QString m_shopName;
};

#endif // PUSHBUTTONSENDER_HPP
