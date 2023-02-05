#ifndef DATACLASS_HPP
#define DATACLASS_HPP

#include <QObject>
#include <QVector>

#include "../Common/ModelStruct.hpp"

class DataClass : public QObject
{
    Q_OBJECT
public:
    explicit DataClass(QObject *parent = nullptr);



private:
    QVector<ModelSettings> m_settingsVec;

};

#endif // DATACLASS_HPP
