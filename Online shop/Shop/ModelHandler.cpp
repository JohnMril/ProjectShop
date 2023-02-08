#include "ModelHandler.hpp"

ModelHandler::ModelHandler(QObject *parent) : QObject(parent)
{
    //    m_placesModels = new QStandardItemModel(0, 2, this);
    //    m_placesModels->setHeaderData(0, Qt::Horizontal, "Name", Qt::DisplayRole);
    //    m_placesModels->setHeaderData(1, Qt::Horizontal, "Date", Qt::DisplayRole);

    m_placesModels = new QStandardItemModel(0, 2, this);
    m_placesModels->setHeaderData(0, Qt::Horizontal, "Name", Qt::DisplayRole);
    m_placesModels->setHeaderData(1, Qt::Horizontal, "Date", Qt::DisplayRole);
}

void ModelHandler::CreateModel(const ModelStruct &modelStruct)
{
    AppendRowToPlacesModel(modelStruct.shop, modelStruct.date);



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



QMultiMap<QString, QStandardItemModel *> ModelHandler::GetMapModelsRaw() const
{
    return m_mapModels;
}



QMultiMap<QString, QSortFilterProxyModel *> ModelHandler::GetMapOfProxyModels() const
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



void ModelHandler::CreateNewModelFromDataClass()
{
   ModelStruct* tmpModelStruct = m_dataClass->GetLastModelStruct();
   ModelSettings* tmpModelSettings = m_dataClass->GetSettingsForModelStruct(tmpModelStruct);

   AppendRowToPlacesModel(tmpModelStruct->shop, tmpModelStruct->date);


   QMultiMap<int, QString> multiMapHeaders;
   for (auto key : tmpModelSettings->mapSettings)
   {
        if(key.enabled)
        {
            multiMapHeaders.insert(key.number, key.keyName);
        }
   }

    m_tmpModel = new QStandardItemModel (tmpModelStruct->modelMap.size(), multiMapHeaders.size(), this);

    int column = 0;
    for(auto value : multiMapHeaders.values())
    {
        m_tmpModel->setHeaderData(column, Qt::Horizontal, tmpModelSettings->mapSettings.value(value).valueName, Qt::DisplayRole);
        column++;
    }

    int row = 0;

    QStringList keysOn = multiMapHeaders.values();

    for (auto element :tmpModelStruct->modelMap)
    {
        for( auto key : keysOn)
        {
            if(element.contains(key))
            {
                m_tmpModel->setData(m_tmpModel->index(row, keysOn.indexOf(key)), element.value(key), Qt::DisplayRole);
            }
        }

        row++;
    }

    m_mapModels.insert(tmpModelStruct->shop, m_tmpModel);
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(m_tmpModel);
    m_mapOfProxy.insert(tmpModelStruct->shop, proxyModel);

    emit CreatedNewModel();

}
