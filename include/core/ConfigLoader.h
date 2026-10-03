// CLASS ConfigLoader:
//     PRIVATE STATE:
//         // A dictionary mapping a Fruit Name (String) to its ProduceSpec
//         DICTIONARY m_produce_db 
        
//         // NEW: A dictionary mapping a Chamber ID (String) to its ChamberSpec
//         DICTIONARY m_chamber_db 
        
//         BOOLEAN m_is_produce_loaded (Default: False)
//         BOOLEAN m_is_chamber_loaded (Default: False)

//     PUBLIC CAPABILITIES:
//         METHOD loadProduceDB(filepath) RETURNS Boolean
//         METHOD loadChamberConfig(filepath) RETURNS Boolean

//         // NEW: Getters that return the ENTIRE dictionary for iteration
//         METHOD getAllProduce() RETURNS Read-Only Reference to m_produce_db
//         METHOD getAllChambers() RETURNS Read-Only Reference to m_chamber_db

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