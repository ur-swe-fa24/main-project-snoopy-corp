add_executable(myExe
    test_robots.cpp
    #createMaps.cpp
)

target_include_directories(myExe
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_link_libraries(myExe
    PRIVATE
        sim_lib)


target_compile_features(myExe PRIVATE cxx_std_17)