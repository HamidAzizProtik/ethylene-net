#include "Produce.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

produceSpec load_produce_config(const std::string& filepath) {
    // open file stream
    std::ifstream file(filepath);
    
    // guard clause for missing/inaccessible files
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file at " << filepath << "\n";
        return {}; 
    }

    // parse stream into nlohmann::json container (disabling exceptions)
    nlohmann::json data = nlohmann::json::parse(file, nullptr, false);
    if (data.is_discarded()) {
        std::cerr << "Error: Malformed JSON syntax (invalid file format).\n";
        return {};
    }

    // check for missing keys using .contains()[cite: 1]
    if (!data.contains("name") || !data.contains("ethylene_ppm") || !data.contains("decay_rate")) {
        std::cerr << "Error: Missing one or more required keys in JSON file.\n";
        return {};
    }

    // check for type mismatches before extracting
    if (!data["name"].is_string() || !data["ethylene_ppm"].is_number() || !data["decay_rate"].is_number()) {
        std::cerr << "Error: Type mismatch! Check your data types (strings vs numbers).\n";
        return {};
    }

    // map JSON keys to struct fields 
    produceSpec spec;
    spec.name         = data["name"].get<std::string>();
    spec.ethylene_ppm = data["ethylene_ppm"].get<double>();
    spec.decay_rate   = data["decay_rate"].get<double>();

    // return populated struct
    return spec;
}