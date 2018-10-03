#ifndef RECIPES_H
#define RECIPES_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>

#include "recipe.h"

class Recipes
{
public:
    Recipes(void);
    ~Recipes(void);

    QList<Recipe *> recipeList(void) const;

    bool read(const QJsonObject &json);

private:
    QList<Recipe *> m_recipeList;
};

#endif // RECIPES_H
