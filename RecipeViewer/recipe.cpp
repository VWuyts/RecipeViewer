#include "recipe.h"

Recipe::Recipe()
{
    m_name = "";
    m_servings = Serving();
    m_ingredients = QList<Ingredients *>();
    m_steps = QStringList();
    m_notes = QStringList();
}

Recipe::~Recipe()
{
    while (!m_ingredients.isEmpty()) delete m_ingredients.takeFirst();
}

QString Recipe::name() const
{
    return m_name;
}

Serving Recipe::servings() const
{
    return m_servings;
}

int Recipe::difficulty() const
{
    return m_difficulty;
}

QList<Ingredients *> Recipe::ingredients() const
{
    return m_ingredients;
}

QStringList Recipe::steps() const
{
    return m_steps;
}

QStringList Recipe::notes() const
{
    return m_notes;
}

bool Recipe::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString()
            && json.contains("servings") && json["servings"].isObject()
            && json.contains("difficulty") && json["difficulty"].isDouble()
            && json.contains("ingredients") && json["ingredients"].isArray()
            && json.contains("steps") && json["steps"].isArray()
            && json.contains("notes") && (json["notes"].isArray() || json["notes"].isNull()))
    {
        m_name = json["name"].toString();
        if (!m_servings.read(json["servings"].toObject())) return false;
        m_difficulty = json["difficulty"].toInt();
        while (!m_ingredients.isEmpty()) delete m_ingredients.takeFirst();
        foreach (const QJsonValue & ingrValue, json["ingredients"].toArray())
        {
            QJsonObject ingrObj = ingrValue.toObject();
            Ingredients *ingredients = new Ingredients();
            if (!ingredients->read(ingrObj))
            {
                return false;
            }
            m_ingredients << ingredients;
        }
        m_steps.clear();
        foreach (const QJsonValue &stepValue, json["steps"].toArray())
        {
            m_steps << stepValue.toString();
        }
        m_notes.clear();
        if (json["notes"].isArray())
        {
            foreach (const QJsonValue &noteValue, json["notes"].toArray())
            {
                m_notes << noteValue.toString();
            }
        }
        return true;
    }
    return false;
}


