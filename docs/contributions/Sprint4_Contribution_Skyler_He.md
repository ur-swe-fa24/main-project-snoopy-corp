# Contributions:
+ Optimized the logic of mongodb database
    - Updated the status of robots without creating multiple new documents
    - Added new robots with unique IDs
    - Created a removed data collections for removed robot and remained their unique IDs

+ Wrote the unit tests for `MongoDBWrapper.cpp` and all tests passed for `upsert` and `movetoRemoved`

+ Correspondingly updated `Robot.cpp`, `SimulationDriver.cpp`, `CMakeLists` to work with MongoDB