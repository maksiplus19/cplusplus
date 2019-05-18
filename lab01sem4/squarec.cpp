#include "squarec.h"

void squareC::draw(QGraphicsScene *s)
{
    QGraphicsItem* item = s->addRect(left_, top_, width_, width_, QPen(Qt::black), QBrush(color_));
    item->setTransformOriginPoint(left_ + width_/2, top_ + width_/2);
    item->setRotation(angle_);
}

double squareC::square()
{
    return width_ * width_;
}

void squareC::move(double new_x, double new_y)
{
    top_ = new_y;
    left_ = new_x;
}
