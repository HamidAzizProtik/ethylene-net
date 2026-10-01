#include "core/ConfigLoader.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;

bool ConfigLoader::loadProduceDB(const std::string& filepath) 
{
    std::ifstream file(filepath);
    
    if (!file.is_open()) 
    {
        std::cerr << "CRITICAL ERROR: Cannot access file at " << filepath << "\n";
        return false;
    }

    json json_data = json::parse(file, nullptr, false);
    
    if (json_data.is_discarded()) 
    {
        std::cerr << "CRITICAL ERROR: Syntax error in JSON file.\n";
        return false;
    }

    if (!json_data.is_array()) 
    {
        std::cerr << "CRITICAL ERROR: produce_db.json must be an Array []\n";
        return false;
    }

    // iterate over the items
    for (const auto& item : json_data) 
    {
        
        if (!item.contains("name") || !item.contains("ethylene_ppm") || !item.contains("decay_rate")) 
        {
            std::cerr << "WARNING: Skipping item missing required fields.\n";
            continue; 
        }

        if (!item["name"].is_string() || !item["ethylene_ppm"].is_number() || !item["decay_rate"].is_number()) 
        {
            std::cerr << "WARNING: Skipping item with wrong data types.\n";
            continue;
        }

        std::string name = item["name"];
        double ethylene = item["ethylene_ppm"];
        double decay = item["decay_rate"];

        if (name.empty() || ethylene < 0.0 || decay < 0.0) 
        {
            std::cerr << "WARNING: Skipping item defying physics or empty name: " << name << "\n";
            continue;
        }

        if (m_produce_db.find(name) != m_produce_db.end()) 
        {
            std::cerr << "WARNING: Duplicate found for " << name << ". Skipping to preserve first entry.\n";
            continue;
        }

        ProduceSpec new_spec;
        new_spec.name = name;
        new_spec.ethylene_ppm = ethylene;
        new_spec.decay_rate = decay;

        m_produce_db[name] = new_spec;
    }
    
    m_is_produce_loaded = true;
    return true;
}

bool ConfigLoader::loadChamberConfig(const std::string& filepath) 
{
    std::ifstream file(filepath);
    if (!file.is_open()) 
    {
        std::cerr << "CRITICAL ERROR: Cannot access file at " << filepath << "\n";
        return false;
    }
    
    json json_data = json::parse(file, nullptr, false);
    if (json_data.is_discarded()) 
    {
        std::cerr << "CRITICAL ERROR: Syntax error in Chamber JSON file.\n";
        return false;
    }
    
    if (!json_data.is_object()) 
    {
        std::cerr << "CRITICAL ERROR: chamber_config must be a JSON Object {}\n";
        return false;
    }
        
    if (!json_data.contains("volume_m3") || !json_data.contains("ach_airflow") || !json_data.contains("default_temp_c")) 
    {
        std::cerr << "CRITICAL ERROR: Chamber config missing required fields.\n";
        return false;
    }

    if (!json_data["volume_m3"].is_number() || !json_data["ach_airflow"].is_number() || !json_data["default_temp_c"].is_number()) 
    {
        std::cerr << "CRITICAL ERROR: Chamber config contains wrong data types.\n";
        return false;
    }

    double vol = json_data["volume_m3"];
    double ach = json_data["ach_airflow"];
    double temp = json_data["default_temp_c"];

    if (vol <= 0.0 || ach < 0.0 || temp < -273.15) 
    {
        std::cerr << "CRITICAL ERROR: Chamber values defy physics.\n";
        return false;
    }

    m_chamber_settings.volume_m3 = vol;
    m_chamber_settings.ach_airflow = ach;
    m_chamber_settings.default_temp_c = temp;

    m_is_chamber_loaded = true;
    return true;
}

const ProduceSpec* ConfigLoader::getProduce(const std::string& produce_name) const 
{
    if (!m_is_produce_loaded) 
    {
        std::cerr << "ERROR: Cannot get produce. Database not loaded.\n";
        return nullptr;
    }

    auto it = m_produce_db.find(produce_name);
    
    if (it == m_produce_db.end()) 
    {
        return nullptr;
    } 
    else 
    {
        return &(it->second);
    }
}

ChamberSpec ConfigLoader::getChamber() const {
    return m_chamber_settings;
}