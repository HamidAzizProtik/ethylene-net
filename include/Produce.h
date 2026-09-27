#pragma once
#include <string>

struct produceSpec 
{
    std::string name;
    float ethylene_ppm;
    float decay_rate;
};

produceSpec loadProduceConfig(const std::string& filepath);