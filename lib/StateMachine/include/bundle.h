#pragma once
#include <measurement.h>
class Bundle
{
public:
    Bundle();
    Bundle(const Bundle &);
    ~Bundle() = default;
    bool contains_measurement();
    void set_measurement(const Measurement ms);
    Measurement get_measurement();
    unsigned long get_measurement_count();
    void increase_measurement_count();

private:
    Measurement measurement = Measurement(0, 0, 0, 0);
    bool has_measurement = false;
    unsigned long measurement_count = 1;
};