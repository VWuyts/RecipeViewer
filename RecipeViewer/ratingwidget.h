#ifndef RATINGWIDGET_H
#define RATINGWIDGET_H

#include <QWidget>
#include <QPainter>

class RatingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RatingWidget(QWidget *parent = nullptr);

    void setMax(int max);
    void setRating(int rating);

private:
    int m_max;
    int m_rating;

    void paintEvent(QPaintEvent *event);
};

#endif // RATINGWIDGET_H
