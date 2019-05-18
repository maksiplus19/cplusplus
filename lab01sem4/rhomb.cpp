#include "rhomb.h"


void rhombus::draw(QGraphicsScene *s)
{
    QPainterPath path;
    path.moveTo(left_ + width_/2, top_);
    path.lineTo(left_, top_ + heigth_/2);
    path.lineTo(left_ + width_/2, top_ + heigth_);
    path.lineTo(left_ + width_, top_ + heigth_/2);
    path.lineTo(left_ + width_/2, top_);

    QGraphicsItem* item = s->addPath(path, QPen(Qt::black), QBrush(color_));
    item->setTransformOriginPoint(left_ + width_/2,top_ + heigth_/2);
    item->setRotation(angle_);
}

double rhombus::square()
{
    return 0.5 * width_ * heigth_;
}

void rhombus::move(double new_x, double new_y)
{
    top_ = new_y;
    left_ = new_x;
}
