#ifndef SQUAREC_H
#define SQUAREC_H

#include "figure.h"

class squareC : public figure
{
protected:
    double top_;
    double left_;
    double width_;
public:
    squareC(double t, double l, double w, QColor color = QColor(0,0,0,50), int angle = 0) : figure(color, angle),
        top_(t), left_(l), width_(w){}
    ~squareC() override = default;
    void draw(QGraphicsScene *s) override;
	double square() override;
    void move(double new_x, double new_y) override;
};

#endif // SQUAREC_H
