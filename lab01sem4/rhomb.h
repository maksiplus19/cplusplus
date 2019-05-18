#pragma once
#include "squarec.h"

class rhombus :
	public squareC
{
protected:
    double heigth_;
public:
    rhombus(double t, double l, double s, double h, QColor color = QColor(0,0,0,50), int angle = 0) :
        squareC(t, l, s, color, angle), heigth_(h){}
    void draw(QGraphicsScene *) override;
	double square() override;
    void move(double new_x, double new_y) override;
    ~rhombus() override  = default;
};

