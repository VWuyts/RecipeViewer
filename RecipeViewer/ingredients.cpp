#include "ingredients.h"

Ingredients::Ingredients()
{
    m_part = "";
    m_ingredientList = QList<Ingredient *>();
}

Ingredients::~Ingredients()
{
    while (!m_ingredientList.isEmpty()) delete m_ingredientList.takeFirst();
}

QString Ingredients::part() const
{
    return m_part;
}

QList<Ingredient *> Ingredients::ingredientList() const
{
    return m_ingredientList;
}

bool Ingredients::read(const QJsonObject &json)
{
    if (json.contains("part") && json["part"].isString()
            && json.contains("ingredient") && json["ingredient"].isArray())
    {
        m_part = json["part"].toString();
        while (!m_ingredientList.isEmpty()) delete m_ingredientList.takeFirst();
        foreach (const QJsonValue &ingrValue, json["ingredient"].toArray())
        {
            QJsonObject ingrObj = ingrValue.toObject();
            Ingredient *ingredient = new Ingredient();
            if (!ingredient->read(ingrObj))
            {
                return false;
            }
            m_ingredientList << ingredient;
        }
        return true;
    }
    return false;
}
