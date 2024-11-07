find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

add_executable(myExe
    # test_robots.cpp
    #createMaps.cpp
    test_wxWidgets.cpp
)

find_package(spdlog REQUIRED)
if (spdlog_FOUND)
  message(STATUS "spdlog found!")
endif()

# add_executable(myExe
#     test_robots.cpp
# )

target_include_directories(myExe
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    ${wxWidgets_INCLUDE_DIRS}  
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
        sim_lib
        ${wxWidgets_LIBRARIES} 
        spdlog::spdlog_header_only
        mongo::mongocxx_shared)


target_compile_features(myExe PRIVATE cxx_std_17)
