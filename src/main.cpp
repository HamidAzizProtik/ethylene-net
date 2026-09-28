#include "Produce.h"
#include <iostream>

using std::cout;

int main()
{
    // loading produce
    produceSpec item = loadProduceConfig("produce.json");

    // printing out information
    cout << "Item name: " << item.name << "\n"
        <<  "Ethylene level (PPM): " << item.ethylene_ppm << "\n"
        <<  "Decay Rate: " << item.decay_rate << "\n";

    return 0;
}
