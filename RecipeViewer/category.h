#ifndef CATEGORY_H
#define CATEGORY_H

#include <QJsonObject>
#include <QString>

class Category
{
public:
    explicit Category(void);

    QString name(void) const;
    QString file(void) const;

    bool read(const QJsonObject &json);

private:
    QString m_name;
    QString m_file;
};

#endif // CATEGORY_H
