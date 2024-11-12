# Logging with spdlog - we will use this logging library for output.
CPMAddPackage("gh:gabime/spdlog@1.14.1")
# Catch2 Unit Testing - this library will be used for unit testing in the future.
CPMAddPackage("gh:catchorg/Catch2@3.6.0") 
# JSON library for Maps
CPMAddPackage("gh:nlohmann/json@3.11.3")
# Add magic_enum using CPM
CPMAddPackage("gh:Neargye/magic_enum@0.9.6")