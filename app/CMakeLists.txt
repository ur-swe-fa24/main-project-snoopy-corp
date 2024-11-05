# Find the wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Include wxWidgets headers
include(${wxWidgets_USE_FILE})

add_executable(myExe
    # test_robots.cpp
    #createMaps.cpp
    test_wxWidgets.cpp
)

target_include_directories(myExe
    PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    ${wxWidgets_INCLUDE_DIRS}  # Add wxWidgets include directories

)

target_link_libraries(myExe
    PRIVATE
        sim_lib
        ${wxWidgets_LIBRARIES} 
        )

        message("wxWidgets Libraries: ${wxWidgets_LIBRARIES}")
        message("wxWidgets Include Dirs: ${wxWidgets_INCLUDE_DIRS}")
        
target_compile_features(myExe PRIVATE cxx_std_17)
