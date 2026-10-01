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