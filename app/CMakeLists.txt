find_package(spdlog REQUIRED)
if (spdlog_FOUND)
  message(STATUS "spdlog found!")
endif()

add_executable(myExe
    test_robots.cpp
)

target_include_directories(myExe
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    
    
)

target_link_libraries(
    myExe
    PRIVATE
        sim_lib
        database
        spdlog::spdlog_header_only
        mongo::mongocxx_shared
)

target_link_libraries(
    database
    PRIVATE
        spdlog::spdlog_header_only
        mongo::mongocxx_shared)




target_compile_features(myExe PRIVATE cxx_std_17)