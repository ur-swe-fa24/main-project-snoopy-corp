find_package(Catch2 3 REQUIRED)

IF (${Catch2_FOUND})
    MESSAGE(STATUS "Found Catch2")
ELSE (${Catch2_FOUND})
    MESSAGE(STATUS "Could not find Catch2. Check to make sure its installed on your system!")
ENDIF (${Catch2_FOUND})

add_executable(test Map_Tests.cpp)

target_compile_features(test PRIVATE cxx_std_17)

# How we link with Catch2!
target_link_libraries(test
  PRIVATE
    Catch2::Catch2WithMain
    myExe
)