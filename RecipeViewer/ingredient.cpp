#include "ingredient.h"

Ingredient::Ingredient()
{
    m_amount = 0;
    m_unit = "";
    m_name = "";
    m_note = "";
}

double Ingredient::amount() const
{
    return m_amount;
}

QString Ingredient::unit() const
{
    return m_unit;
}

QString Ingredient::name() const
{
    return m_name;
}

QString Ingredient::note() const
{
    return m_note;
}

bool Ingredient::read(const QJsonObject &json)
{
    if (json.contains("amount") && json["amount"].isDouble()
            && json.contains("unit") && json["unit"].isString()
            && json.contains("name") && json["name"].isString()
            && json.contains("note") && json["note"].isString())
    {
        m_amount = json["amount"].toDouble();
        m_unit = json["unit"].toString();
        m_name = json["name"].toString();
        m_note = json["note"].toString();
        return true;
    }
    return false;
}
