#include "categories.h"
#include <QDebug>

Categories::Categories()
{
    m_categoryList = QList<Category *>();
}

Categories::~Categories()
{
    while (!m_categoryList.isEmpty()) delete m_categoryList.takeFirst();
}

QList<Category *> Categories::categoryList() const
{
    return m_categoryList;
}

bool Categories::read(const QJsonObject &json)
{
    if (json.contains("categories") && json["categories"].isArray())
    {
        while (!m_categoryList.isEmpty()) delete m_categoryList.takeFirst();
        foreach (const QJsonValue &catValue, json["categories"].toArray())
        {
            QJsonObject catObj = catValue.toObject();
            Category *category = new Category();
            if (!category->read(catObj))
            {
                return false;
            }
            m_categoryList << category;
        }
        return true;
    }

    return false;
}


