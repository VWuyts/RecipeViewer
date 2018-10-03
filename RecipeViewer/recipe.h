#ifndef RECIPE_H
#define RECIPE_H

#include <limits>
#include <QJsonArray>
#include <QList>
#include <QString>

#include "ingredients.h"
#include "serving.h"

class Recipe
{
public:
    explicit Recipe(void);
    ~Recipe(void);

    QString name(void) const;
    Serving servings(void) const;
    int difficulty(void) const;
    QList<Ingredients *> ingredients(void) const;
    QStringList steps(void) const;
    QStringList notes(void) const;

    bool read(const QJsonObject &json);

private:
    QString m_name;
    Serving m_servings;
    int m_difficulty;
    QList<Ingredients *> m_ingredients;
    QStringList m_steps;
    QStringList m_notes;
};

#endif // RECIPE_H
