add_executable(test_robots
    test_robots.cpp

)

target_include_directories(test_robots
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(test_robots
    PRIVATE
        sim_lib)

target_compile_features(test_robots PRIVATE cxx_std_17)