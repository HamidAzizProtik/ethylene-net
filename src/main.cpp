// START MAIN:
//     CREATE loader instance
    
//     LOAD produce database
//     LOAD chamber database

//     IF produce loaded successfully:
//         GET entire_produce_dictionary FROM loader
        
//         FOR EACH [fruit_name, fruit_details] IN entire_produce_dictionary:
//             PRINT fruit_name
//             PRINT fruit_details.ethylene_ppm
//             PRINT fruit_details.decay_rate

//     IF chambers loaded successfully:
//         GET entire_chamber_dictionary FROM loader
        
//         FOR EACH [chamber_name, chamber_details] IN entire_chamber_dictionary:
//             PRINT chamber_name
//             PRINT chamber_details.volume_m3
//             PRINT chamber_details.ach_airflow

// END MAIN

#include "core/ConfigLoader.h"
#include <iostream>

int main() 
{
    ConfigLoader loader;

    // test loader
    bool ProduceCheck = loader.loadProduceDB("../data/produce_db.json");
    bool ContainerCheck = loader.loadChamberConfig("../data/chamber_config.json");

    std::cout << "Produce DB Load: ";
        if (ProduceCheck) 
        {
            std::cout << "PASS\n";
        } 
        else 
        {
            std::cout << "FAIL\n";
        }

        std::cout << "Chamber Config Load: ";
        if (ContainerCheck) 
        {
            std::cout << "PASS\n\n";
        } 
        else 
        {
            std::cout << "FAIL\n\n";
        }

    // returns ChamberSpec struct copy
    if (ContainerCheck) 
    {
        ChamberSpec chamber = loader.getChamber();
        std::cout << "--- CHAMBER SPECIFICATIONS ---\n"
                << "Volume:       " << chamber.volume_m3 << " m^3\n"
                << "ACH Airflow:  " << chamber.ach_airflow << "\n"
                << "Default Temp: " << chamber.default_temp_c << " C\n\n";
    }

    // returns const ProduceSpec* pointer
    if (ProduceCheck) 
    {
        const ProduceSpec* spec = loader.getProduce("Apple");
        if (spec != nullptr) 
        {
            std::cout << "--- PRODUCE SPECIFICATION ---\n"
                    << "Name:         " << spec->name << "\n"
                    << "Ethylene PPM: " << spec->ethylene_ppm << "\n"
                    << "Decay Rate:   " << spec->decay_rate << "\n";
        } 
        else 
        {
            std::cout << "Item not found in database.\n";
        }
    }

    return 0;
}