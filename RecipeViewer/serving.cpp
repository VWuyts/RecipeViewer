#include "serving.h"

Serving::Serving()
{
    m_amount = 1;
    m_unit = "";
}

int Serving::amount() const
{
    return m_amount;
}

QString Serving::unit() const
{
    return m_unit;
}

bool Serving::read(const QJsonObject &json)
{
    if (json.contains("amount") && json["amount"].isDouble()
            && json.contains("unit") && json["unit"].isString())
    {
        m_amount = abs(json["amount"].toInt());
        m_unit = json["unit"].toString();
        return true;
    }
    return false;
}
