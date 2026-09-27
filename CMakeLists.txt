cmake_minimum_required(VERSION 3.16)
project(EthyleneNet VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(nlohmann_json 3.2.0 REQUIRED)

set(SOURCES
    src/Produce.cpp
    src/main.cpp
)

add_executable(ethylene_net ${SOURCES})

target_include_directories(ethylene_net PRIVATE include)

target_link_libraries(ethylene_net PRIVATE nlohmann_json::nlohmann_json)