#pragma once
#include <string>

struct ProduceSpec 
{
    std::string name;
    double ethylene_ppm;
    double decay_rate;
};

struct ChamberSpec
{
    double volume_m3 { 0.0 };
    double ach_airflow { 0.0 };
    double default_temp_c { 0.0 };
};