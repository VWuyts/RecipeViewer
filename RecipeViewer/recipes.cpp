#include "recipes.h"

Recipes::Recipes()
{
    m_recipeList = QList<Recipe *>();
}

Recipes::~Recipes()
{
    while (!m_recipeList.isEmpty()) delete m_recipeList.takeFirst();
}

QList<Recipe *> Recipes::recipeList() const
{
    return m_recipeList;
}

bool Recipes::read(const QJsonObject &json)
{
    if (json.contains("recipes") && json["recipes"].isArray())
    {
        while (!m_recipeList.isEmpty()) delete m_recipeList.takeFirst();
        foreach (const QJsonValue &recipeValue, json["recipes"].toArray())
        {
            QJsonObject recipeObj = recipeValue.toObject();
            Recipe *recipe = new Recipe();
            if (!recipe->read(recipeObj))
            {
                return false;
            }
            m_recipeList << recipe;
        }
        return true;
    }
    return false;
}


