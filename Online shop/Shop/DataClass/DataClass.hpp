#ifndef DATACLASS_HPP
#define DATACLASS_HPP

#include <QObject>
#include <QVector>
#include <QSet>

#include "../Common/ModelStruct.hpp"

class DataClass : public QObject
{
    Q_OBJECT
public:
    explicit DataClass(QObject *parent = nullptr);

    void Insert(const ModelSettings& settings);

    QSet<int> FindForSettings(const ModelStruct& modelStruct);

    void AppendNewModelStruct(const ModelStruct& model);

    QVector<ModelStruct> GetModelStructVec() const;
    ModelStruct GetLastModelStruct() const;
    ModelStruct GetModelStructByName(const QString& shopName) const;

private:
    QVector<ModelSettings> m_settingsVec;
    QVector<ModelStruct> m_modelStructVec;


};

#endif // DATACLASS_HPP
