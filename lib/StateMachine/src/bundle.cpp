#include "bundle.h"

Bundle::Bundle()
{
    this->measurement = Measurement(0, 0, 0, 0);
    this->measurement_count = 1;
}
Bundle::Bundle(const Bundle &other) : measurement(other.measurement), measurement_count(other.measurement_count) {}

bool Bundle::contains_measurement()
{
    return this->has_measurement;
}

void Bundle::set_measurement(const Measurement ms)
{
    this->measurement = ms;
    this->has_measurement = true;
}

Measurement Bundle::get_measurement()
{
    return this->measurement;
}

unsigned long Bundle::get_measurement_count()
{
    return this->measurement_count;
}

void Bundle::increase_measurement_count()
{
    this->measurement_count += 1;
}