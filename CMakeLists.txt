cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Building this awesome project!")
project(SnoppyCorp LANGUAGES CXX)

include(dependencies/get_cpm.cmake)
include(dependencies/dependencies.cmake)

# Setup the libraries for use!
add_library(sim_lib
src/sim_src/robot.cpp
src/sim_src/scrubber_robot.cpp
src/sim_src/shampoo_robot.cpp
src/sim_src/vacuum_robot.cpp
src/sim_src/simulation_driver.cpp

)

target_include_directories(sim_lib
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include
)

# Link spdlog 
target_link_libraries(sim_lib
    spdlog::spdlog
)

add_subdirectory(app)