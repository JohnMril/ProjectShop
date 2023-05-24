#include "ModelHandler.hpp"

ModelHandler::ModelHandler(QObject *parent) : QObject(parent)
{
    //    m_placesModels = new QStandardItemModel(0, 2, this);
    //    m_placesModels->setHeaderData(0, Qt::Horizontal, "Name", Qt::DisplayRole);
    //    m_placesModels->setHeaderData(1, Qt::Horizontal, "Date", Qt::DisplayRole);

    m_placesModels = new QStandardItemModel(0, 3, this);
    m_placesModels->setHeaderData(0, Qt::Horizontal, "Name", Qt::DisplayRole);
    m_placesModels->setHeaderData(1, Qt::Horizontal, "Date", Qt::DisplayRole);
    m_placesModels->setHeaderData(2, Qt::Horizontal, "SqlSend", Qt::DisplayRole);

}

void ModelHandler::CreateModel(const ModelStruct &modelStruct)
{


    AppendRowToPlacesModel(modelStruct.shop, modelStruct.date);

    if(m_mapModels.contains(modelStruct.shop))
    {
       delete m_mapOfProxy.value(modelStruct.shop);
       delete m_mapModels.value(modelStruct.shop);
    }


    m_tmpModel = new QStandardItemModel (modelStruct.modelMap.size(), 10, this);
    m_tmpModel->setHeaderData(0, Qt::Horizontal, "№", Qt::DisplayRole);
    m_tmpModel->setHeaderData(1, Qt::Horizontal, "VendorId", Qt::DisplayRole);
    m_tmpModel->setHeaderData(2, Qt::Horizontal, "VendorCode", Qt::DisplayRole);
    m_tmpModel->setHeaderData(3, Qt::Horizontal, "ProductName", Qt::DisplayRole);
    m_tmpModel->setHeaderData(4, Qt::Horizontal, "ProductDescripition", Qt::DisplayRole);
    m_tmpModel->setHeaderData(5, Qt::Horizontal, "Width", Qt::DisplayRole);
    m_tmpModel->setHeaderData(6, Qt::Horizontal, "Mass", Qt::DisplayRole);
    m_tmpModel->setHeaderData(7, Qt::Horizontal, "Price", Qt::DisplayRole);
    m_tmpModel->setHeaderData(8, Qt::Horizontal, "CategoryId", Qt::DisplayRole);
    m_tmpModel->setHeaderData(9, Qt::Horizontal, "area", Qt::DisplayRole);

    int row = 0;
    for (auto element : modelStruct.modelMap)
    {

        m_tmpModel->setData(m_tmpModel->index(row, 0), row+1, Qt::DisplayRole);

        if (element.contains("product_id"))
        {
            m_tmpModel->setData(m_tmpModel->index(row, 1), element.value("product_id"), Qt::DisplayRole);
        }
        if (element.contains("product_id"))
        {
            m_tmpModel->setData(m_tmpModel->index(row, 2), element.value("product_id"), Qt::DisplayRole);
        }
        if (element.contains("product_full_name"))
        {
            m_tmpModel->setData(m_tmpModel->index(row, 3), element.value("product_full_name").toString(), Qt::DisplayRole);
        }
        if (element.contains("product_description"))
        {
            m_tmpModel->setData(m_tmpModel->index(row, 4), element.value("product_description").toString(), Qt::DisplayRole);
        }
        if (element.contains("product_width"))
        {
            m_tmpModel->setData(m_tmpModel->index(row, 5), element.value("product_width"), Qt::DisplayRole);
        }
        if (element.contains("product_weight"))
        {
            m_tmpModel->setData(m_tmpModel->index(row, 6), element.value("product_weight"), Qt::DisplayRole);
        }
        if (element.contains("product_price_retail"))
        {
            m_tmpModel->setData(m_tmpModel->index(row, 7), element.value("product_price_retail"), Qt::DisplayRole);
            if(element.contains("currency_name"))
            {
                m_tmpModel->setData(m_tmpModel->index(row, 7), element.value("currency_name").toString(), Qt::ToolTipRole);
            }
        }
        if (element.contains("category_id"))
        {
            m_tmpModel->setData(m_tmpModel->index(row, 8), element.value("category_id"), Qt::DisplayRole);
        }
        if (element.contains("product_length") && element.contains("product_width"))
        {
            m_tmpModel->setData(m_tmpModel->index(row, 9), element.value("product_length").toFloat()*element.value("product_width").toFloat(), Qt::DisplayRole);
        }
        row++;
    }

    m_mapModels.insert(modelStruct.shop, m_tmpModel);
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(m_tmpModel);
    m_mapOfProxy.insert(modelStruct.shop, proxyModel);
}

void ModelHandler::AppendRowToPlacesModel(QVariant name, QVariant data)
{
    for(int row = 0 ; row < m_placesModels->rowCount(); row++)
    {
        if(m_placesModels->data(m_placesModels->index(row, 0)).toString().contains(name.toString()))
        {
            m_placesModels->setData(m_placesModels->index(row, 1), data);

            return;
        }
    }

    QList<QStandardItem*> row;

    QStandardItem* itemName = new QStandardItem(name.toString());
    QStandardItem* itemData = new QStandardItem(data.toString());

    row.append(itemName);
    row.append(itemData);

    m_placesModels->appendRow(row);
}



void ModelHandler::CreateModels(QVector<ModelStruct> &modelsStructVec)
{
    for (auto element : modelsStructVec)
    {
        CreateModel(element);
    }
}



QStandardItemModel* ModelHandler::GetPlacesModels() const
{
    return m_placesModels;
}



QStandardItemModel* ModelHandler::GetMainShop() const
{
    return m_tmpModel;
}



void ModelHandler::RemoveRows(int row)
{
    m_tmpModel->removeRow(row);
}



QMap<QString, QStandardItemModel *> ModelHandler::GetMapModelsRaw() const
{
    return m_mapModels;
}



QMap<QString, QSortFilterProxyModel *> ModelHandler::GetMapOfProxyModels() const
{
    return m_mapOfProxy;
}



void ModelHandler::SetDataClass(DataClass *dataClass)
{
    m_dataClass = dataClass;
}



QSortFilterProxyModel *ModelHandler::GetLastProxyModel() const
{
    return m_mapOfProxy.value(m_mapModels.key(m_tmpModel));
}



void ModelHandler::CreateModelByString(QString modelName)
{
    bool state;
    ModelStruct model = m_dataClass->GetModelStructByName(modelName, state);
    if(state)
    {
        CreateModel_1(model);
    }
}



void ModelHandler::CreateModel_1(const ModelStruct &modelStruct)
{


    AppendRowToPlacesModel(modelStruct.shop, modelStruct.date);

    if(m_mapModels.contains(modelStruct.shop))
    {
       delete m_mapOfProxy.value(modelStruct.shop);
       delete m_mapModels.value(modelStruct.shop);
    }
    //FIXME memleak
    QStandardItemModel* itemModel = new QStandardItemModel(modelStruct.rowCount(), modelStruct.columnCount(), this);

    int column = 0;
    for(const QString& headerName : modelStruct.setAttributs)
    {
        itemModel->setHeaderData(column, Qt::Horizontal, headerName, Qt::DisplayRole);
        column++;
    }


    for(uint row = 0; row < modelStruct.rowCount(); row++)
    {
        column = 0;
        for(const QString& keyName : modelStruct.setAttributs)
        {
            QModelIndex index = itemModel->index(row, column);
            if(modelStruct.modelMap.at(row).contains(keyName))
            {
                itemModel->setData(index, modelStruct.modelMap.at(row).value(keyName));
            }

            column++;
        }
    }

    m_mapModels.insert(modelStruct.shop, itemModel);

    QSortFilterProxyModel* tmpProxy = new QSortFilterProxyModel(this);
    tmpProxy->setSourceModel(itemModel);

    m_mapOfProxy.insert(modelStruct.shop, tmpProxy);


    emit CreatedNewModel(modelStruct.shop);
}

QModelIndex ModelHandler::GetIndexOfPlacesModelByName(QString shopName)
{
    for(int row = 0 ; row < m_placesModels->rowCount(); row++)
    {
        if(m_placesModels->data(m_placesModels->index(row, 0)).toString().contains(shopName))
        {
            return m_placesModels->index(row, 2);
        }
    }
    return QModelIndex();
}


