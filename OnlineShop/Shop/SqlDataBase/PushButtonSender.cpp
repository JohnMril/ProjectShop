#include "PushButtonSender.hpp"

PushButtonSender::PushButtonSender(QString shopName,QWidget *parent)
    :QPushButton(parent),
      m_shopName(shopName)
{
    this->setText("Sql");
    connect(this, &PushButtonSender::clicked, this, &PushButtonSender::ButtonClicked);
}

QString PushButtonSender::shopName() const
{
    return m_shopName;
}

void PushButtonSender::ButtonClicked()
{
    emit Clicked(m_shopName);
}
