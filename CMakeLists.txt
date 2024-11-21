cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
message("Building this awesome project!")

# Set the CMake install prefix for MongoDB C++ driver
set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/libs/mongo-cxx-driver")
message("CMake install prefix: ${CMAKE_INSTALL_PREFIX}")

# Project name
project(SnoppyCorp LANGUAGES CXX)

# Include dependencies
include(dependencies/get_cpm.cmake)
include(dependencies/dependencies.cmake)

# Add the sim_lib library with the necessary source files
add_library(sim_lib
  src/sim_src/robot.cpp
  src/sim_src/scrubber_robot.cpp
  src/sim_src/shampoo_robot.cpp
  src/sim_src/vacuum_robot.cpp
  src/sim_src/simulation_driver.cpp
  src/sim_src/map.cpp
  src/sim_src/dashboard.cpp
)


target_include_directories(sim_lib
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)


add_library(database
  src/database/mongoDBWrapper.cpp
)

target_include_directories(database
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)



# Find and link MongoDB C++ driver libraries
find_package(mongocxx REQUIRED)
if (mongocxx_FOUND)
  message(STATUS "mongocxx found!")
endif()

find_package(bsoncxx REQUIRED)
if (bsoncxx_FOUND)
  message(STATUS "bsoncxx found!")
endif()

find_package(wxWidgets REQUIRED COMPONENTS core base)
if (wxWidgets_FOUND)
  message(STATUS "wxWidgets found!")
endif()
include(${wxWidgets_USE_FILE})

target_link_libraries(sim_lib
  nlohmann_json::nlohmann_json
  magic_enum
)

# Add wxwidget library with necessary source files
add_library(wxwidgets_lib
  src/wxwidgets/wxwidgets.cpp
)

target_include_directories(wxwidgets_lib
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_link_libraries(wxwidgets_lib 
  ${wxWidgets_LIBRARIES}
  nlohmann_json::nlohmann_json
  magic_enum
)

add_subdirectory(app)
add_subdirectory(tests)
