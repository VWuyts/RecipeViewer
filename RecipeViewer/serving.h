#ifndef SERVING_H
#define SERVING_H

#include <QJsonObject>

class Serving
{
public:
    explicit Serving(void);

    int amount(void) const;
    QString unit(void) const;

    bool read(const QJsonObject &json);

private:
    int m_amount;
    QString m_unit;
};

#endif // SERVING_H
