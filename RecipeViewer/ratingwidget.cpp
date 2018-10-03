#include "ratingwidget.h"

RatingWidget::RatingWidget(QWidget *parent) : QWidget(parent)
{
    m_max = 3;
    m_rating = 1;
}

void RatingWidget::setMax(int max)
{
    if (m_max == max)
        return;

    if (max > 0)
        m_max = max;
}

void RatingWidget::setRating(int rating)
{
    if (m_rating == rating)
        return;

    if (rating > 0 and rating <= m_max)
        m_rating = rating;
    else
        m_rating = rating < 0 ? 0 : m_max;
}

void RatingWidget::paintEvent(QPaintEvent *event)
{
    (void) event;

    QPainter p(this);
    int diameter = width() / m_max - 10;
    if (diameter > height())
        diameter = height() - 10;

    // outlines
    p.setPen(Qt::black);
    p.setBrush(Qt::yellow);
    for (int i = 0; i < m_max; i++)
    {
        if (i >= m_rating)
            p.setBrush(Qt::transparent);
        p.save();
        p.translate(i * (diameter + 10) + (diameter + 10) / 2, (height() - diameter) / 2);
        p.drawEllipse(0, 0, diameter, diameter);
        p.restore();
    }
}
