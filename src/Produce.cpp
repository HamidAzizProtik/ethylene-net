// Parsing Engine (src/Produce.cpp)

// This file implements how data is read from disk into RAM.

//     Include Headers: Include "Produce.hpp", <fstream> (LearnCpp 28.6), <iostream>, and <nlohmann/json.hpp>.

//     File Stream Handling:

//         Instantiate std::ifstream file(filepath).

//         Guard Clause: Check if (!file.is_open()). If it fails, log an error to std::cerr and return an 
//         empty or default struct.

//     JSON Extraction:

//         Instantiate an nlohmann::json object (e.g., nlohmann::json data).

//         Parse the stream using file >> data; or nlohmann::json::parse(file).

//     Struct Population:

//         Declare a ProduceSpec spec;.

//         Extract JSON values using .at("key").get<type>() or bracket operator data["key"] and assign them to 
//         spec.name, spec.ethylene_ppm, and spec.decay_rate.

//     Return: Return spec.

#include "Produce.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

produceSpec loadProduceConfig(const std::string& filepath) 
{
    std::ifstream readFile{ filepath };

    if (!readFile)
    {
        std::cerr << "Error: could not find file at " << filepath << "\n";
        return {};
    }

    json data = json::parse(readFile);

}