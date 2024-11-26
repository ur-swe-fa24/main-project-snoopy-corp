find_package(Catch2 3 REQUIRED)

IF (${Catch2_FOUND})
    MESSAGE(STATUS "Found Catch2")
ELSE (${Catch2_FOUND})
    MESSAGE(STATUS "Could not find Catch2. Check to make sure its installed on your system!")
ENDIF (${Catch2_FOUND})

add_executable(map_test Map_Tests.cpp)
add_executable(clean_test cleaning_tests.cpp)
add_executable(mongodb_test mongodb_tests.cpp)
add_executable(assignment_test assignment_tests.cpp)

target_compile_features(map_test PRIVATE cxx_std_17)
target_compile_features(clean_test PRIVATE cxx_std_17)
target_compile_features(database PRIVATE cxx_std_17)

# How we link with Catch2!
target_link_libraries(map_test
  PRIVATE
    Catch2::Catch2WithMain
    sim_lib
)

target_link_libraries(clean_test
  PRIVATE
    Catch2::Catch2WithMain
    sim_lib
)

target_link_libraries(assignment_test
  PRIVATE
    Catch2::Catch2WithMain
    sim_lib
)


target_link_libraries(mongodb_test
  PRIVATE
    Catch2::Catch2WithMain
    spdlog::spdlog_header_only
    mongo::mongocxx_shared
    sim_lib
    database

)


