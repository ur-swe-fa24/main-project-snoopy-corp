add_executable(myExe
    test_robots.cpp
)

target_include_directories(myExe
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/bsoncxx/v_noabi>
    $<BUILD_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/mongocxx/v_noabi>
    
    
)

target_link_libraries(
    myExe
    PRIVATE
        sim_lib
        mongo::mongocxx_shared)
        


target_compile_features(myExe PRIVATE cxx_std_17)