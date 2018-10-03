#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <limits>
#include <QJsonObject>
#include <QString>

class Ingredient
{
public:
    explicit Ingredient(void);

    double amount(void) const;
    QString unit(void) const;
    QString name(void) const;
    QString note(void) const;

    bool read(const QJsonObject &json);

private:
    double m_amount;
    QString m_unit;
    QString m_name;
    QString m_note;
};

#endif // INGREDIENT_H
