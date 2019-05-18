#include "measure.h"

double measure::get_temp()
{
    return temperature_;
}

int measure::get_id()
{
    return city_id_;
}

QString measure::get_name()
{
    return city_name_;
}
