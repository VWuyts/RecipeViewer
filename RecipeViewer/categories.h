#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>

#include "category.h"

class Categories
{
public:
    Categories(void);
   ~Categories(void);

    QList<Category *> categoryList(void) const;

    bool read(const QJsonObject & json);

private:
    QList<Category *> m_categoryList;
};

#endif // CATEGORIES_H
