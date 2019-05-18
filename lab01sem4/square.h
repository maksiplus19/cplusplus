#ifndef SQUARE_H
#define SQUARE_H

#include "QPoint"
#include "figure.h"

class square_class : public figure
{
public:
    square_class();
    virtual double square();
};

#endif // SQUARE_H
