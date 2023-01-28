#include "ModelHandler.hpp"

ModelHandler::ModelHandler(QObject *parent) : QObject(parent)
{
//    m_placesModels = new QStandardItemModel(0, 2, this);
//    m_placesModels->setHeaderData(0, Qt::Horizontal, "Name", Qt::DisplayRole);
//    m_placesModels->setHeaderData(1, Qt::Horizontal, "Date", Qt::DisplayRole);


}

void ModelHandler::CreateModel(ModelStruct modelStruct)
{
    m_placesModels = new QStandardItemModel(1, 2, this);
    m_placesModels->setHeaderData(0, Qt::Horizontal, "Name", Qt::DisplayRole);
    m_placesModels->setHeaderData(1, Qt::Horizontal, "Date", Qt::DisplayRole);

    m_placesModels->setData(m_placesModels->index(0,0), modelStruct.shop);
    m_placesModels->setData(m_placesModels->index(0,1), modelStruct.data);

    m_mainShop = new QStandardItemModel (modelStruct.modelMap.size(), 10, this);
    m_mainShop->setHeaderData(0, Qt::Horizontal, "№", Qt::DisplayRole);
    m_mainShop->setHeaderData(1, Qt::Horizontal, "VendorId", Qt::DisplayRole);
    m_mainShop->setHeaderData(2, Qt::Horizontal, "VendorCode", Qt::DisplayRole);
    m_mainShop->setHeaderData(3, Qt::Horizontal, "ProductName", Qt::DisplayRole);
    m_mainShop->setHeaderData(4, Qt::Horizontal, "ProductDescripition", Qt::DisplayRole);
    m_mainShop->setHeaderData(5, Qt::Horizontal, "Width", Qt::DisplayRole);
    m_mainShop->setHeaderData(6, Qt::Horizontal, "Mass", Qt::DisplayRole);
    m_mainShop->setHeaderData(7, Qt::Horizontal, "Price", Qt::DisplayRole);
    m_mainShop->setHeaderData(8, Qt::Horizontal, "CategoryId", Qt::DisplayRole);
    m_mainShop->setHeaderData(9, Qt::Horizontal, "area", Qt::DisplayRole);

    int row = 0;
    for (auto element : modelStruct.modelMap)
    {

        m_mainShop->setData(m_mainShop->index(row, 0), row+1, Qt::DisplayRole);

        if (element.contains("product_id"))
        {
            m_mainShop->setData(m_mainShop->index(row, 1), element.value("product_id"), Qt::DisplayRole);
        }
        if (element.contains("product_id"))
        {
            m_mainShop->setData(m_mainShop->index(row, 2), element.value("product_id"), Qt::DisplayRole);
        }
        if (element.contains("product_full_name"))
        {
            m_mainShop->setData(m_mainShop->index(row, 3), element.value("product_full_name"), Qt::DisplayRole);
        }
        if (element.contains("product_description"))
        {
            m_mainShop->setData(m_mainShop->index(row, 4), element.value("product_description"), Qt::DisplayRole);
        }
        if (element.contains("product_width"))
        {
            m_mainShop->setData(m_mainShop->index(row, 5), element.value("product_width"), Qt::DisplayRole);
        }
        if (element.contains("product_weight"))
        {
            m_mainShop->setData(m_mainShop->index(row, 6), element.value("product_weight"), Qt::DisplayRole);
        }
        if (element.contains("product_price_retail"))
        {
            m_mainShop->setData(m_mainShop->index(row, 7), element.value("product_price_retail"), Qt::DisplayRole);
            if(element.contains("currency_name"))
            {
                m_mainShop->setData(m_mainShop->index(row, 7), element.value("currency_name"), Qt::ToolTipRole);
            }
        }
        if (element.contains("category_id"))
        {
            m_mainShop->setData(m_mainShop->index(row, 8), element.value("category_id"), Qt::DisplayRole);
        }
        if (element.contains("product_length") && element.contains("product_width"))
        {
            m_mainShop->setData(m_mainShop->index(row, 9), element.value("product_length").toFloat()*element.value("product_width").toFloat(), Qt::DisplayRole);
        }
        row++;
    }
}



QStandardItemModel* ModelHandler::GetPlacesModels() const
{
    return m_placesModels;
}



QStandardItemModel* ModelHandler::GetMainShop() const
{
    return m_mainShop;
}



void ModelHandler::RemoveRows(int row)
{
    m_mainShop->removeRow(row);
}
