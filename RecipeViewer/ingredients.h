#ifndef INGREDIENTS_H
#define INGREDIENTS_H

#include <QJsonArray>
#include <QList>

#include "ingredient.h"

class Ingredients
{
public:
    explicit Ingredients(void);
    ~Ingredients(void);

    QString part(void) const;
    QList<Ingredient*> ingredientList(void) const;

    bool read(const QJsonObject &json);

private:
    QString m_part;
    QList<Ingredient *> m_ingredientList;
};

#endif // INGREDIENTS_H
