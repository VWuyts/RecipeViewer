#include "category.h"

Category::Category()
{
    m_name = "";
    m_file = "";
}

QString Category::name() const
{
    return m_name;
}

QString Category::file() const
{
    return m_file;
}

bool Category::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString()
            && json.contains("file") && json["file"].isString())
    {
        m_name = json["name"].toString();
        m_file = json["file"].toString();
        return true;
    }
    return false;
}
