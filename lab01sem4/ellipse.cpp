#include "ellipse.h"

void ellipse::draw(QGraphicsScene *s)
{
    QGraphicsItem* item = s->addEllipse(center_.first-h_radius_, center_.second-v_radius_, 2*h_radius_, 2*v_radius_, QPen(Qt::black), QBrush(color_));
    item->setTransformOriginPoint(center_.first, center_.second);
    item->setRotation(angle_);
}

double ellipse::square()
{
    return 3.14 * v_radius_ * h_radius_;
}

void ellipse::move(double new_x, double new_y)
{
    center_.first = new_x;
    center_.second = new_y;
}
