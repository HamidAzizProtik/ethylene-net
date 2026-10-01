#pragma once

#include "Types.h"
#include <unordered_map>
#include <string>

class ConfigLoader
{
private:
    // dictionary mapping string into ProductSpec
    std::unordered_map<std::string, ProduceSpec> m_produce_db; 
    ChamberSpec m_chamber_settings;
    
    // safety
    bool m_is_produce_loaded{false};
    bool m_is_chamber_loaded{false};

public:
    // load stuff
    bool loadProduceDB(const std::string& filepath);
    bool loadChamberConfig(const std::string& filepath);

    // pointer of data
    const ProduceSpec* getProduce(const std::string& produce_name) const;
    ChamberSpec getChamber() const;
};