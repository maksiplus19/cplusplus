#ifndef FIGURE_H
#define FIGURE_H

#include "QGraphicsScene"
#include "QGraphicsItem"
#include "QColor"

class figure
{
public:
    figure(QColor color, int angle) : color_(color), angle_(angle){}
    virtual ~figure() = default;
    virtual void draw(QGraphicsScene *) = 0;
    virtual double square() = 0;
    virtual void move(double new_x, double new_y) = 0;
protected:
    int angle_;
    QColor color_;
};

#endif // FIGURE_H
