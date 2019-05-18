#ifndef MEASURE_H
#define MEASURE_H

#include "QString"

class measure
{
private:
    double temperature_;
    int city_id_;
    QString city_name_;
public:
    measure() = default;
    measure(double t, int id, QString name):temperature_(t), city_id_(id), city_name_(name){}
    double get_temp();
    int get_id();
    QString get_name();
//    measure(const measure&) = delete;
};

#endif // MEASURE_H
