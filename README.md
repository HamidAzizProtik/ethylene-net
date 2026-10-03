# Ethylene Net

A quick C++ logistics simulation engine designed to model ethylene accumulation, helping reliably reduce food waste by suggesting actionable kitchen logistics like advice on optimising space to improve remaining quality life of food.

## Current State
* Currently implementing a simple configuration subsystem that ingests JSON parameters for produce decay models and chamber dimensions into memory structures.

## Features to be implemented

* Modern inventory and volume configuration

* Real time telemetery plotting of remaining quality life

* Cross contamination and priority alerts

* Data saving after every session

* Native Desktop UI

## Getting Started

These instructions will get you a copy of the project up and running on your local
machine for development and testing purposes.


### Prerequisites
To build and run this project, you must have the following installed:
*   **C++ Compiler:** GCC or Clang (Must support C++20 standard)
*   **Build System:** CMake (v3.10 or higher) and Make/Ninja
*   **Dependencies:** `nlohmann/json` (C++ JSON library)

### Installing & Building

This project uses CMake for out-of-source builds to prevent cluttering the source directories.

```bash
# 1. Clone the repository
git clone https://github.com/SalmonTree1/ethylene-net
cd ethylene-net

# 2. Create the build directory
mkdir -p build
cd build

# 3. Generate build files and compile
cmake ..
cmake --build .
```