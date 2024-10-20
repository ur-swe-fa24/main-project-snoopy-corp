cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Building this awesome project!")
project(adapter LANGUAGES CXX)

include(dependencies/get_cpm.cmake)
include(dependencies/dependencies.cmake)

# Setup the libraries for use!
add_library(

)

target_include_directories(
    PUBLIC
   
)

# Link spdlog to the adapters library
target_link_libraries(adapters
    spdlog::spdlog
)

add_subdirectory(app)