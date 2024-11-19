#define CATCH_CONFIG_MAIN
#include "database/mongoDBWrapper.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_approx.hpp>
#include <iostream>

// Ensure only one instance of mongocxx::instance exists
mongocxx::instance& getMongoInstance(){
        static mongocxx::instance instance{};
        return instance;
}

TEST_CASE("MongoDBWrapper Unit Tests", "[MongoDBWrapper]") {
    getMongoInstance(); // Ensure MongoDB driver is initialized

    // Setup test parameters
    const std::string testUri = "mongodb://localhost:27017";
    const std::string testDbName = "test_robot_db";
    const std::string activeCollection = "active_robots";
    const std::string removedCollection = "removed_robots";

    // Create a test MongoDB wrapper
    MongoDBWrapper mongoWrapper(testUri, testDbName, activeCollection, removedCollection);

    SECTION("Upsert Robot Data") {
        int robotId = 101;
        std::string type = "Scrubber";
        std::string status = "Active";
        int location = 5;
        std::string mapName = "TestMap";
        std::string roomStatus = "Clean";

        REQUIRE_NOTHROW(mongoWrapper.upsertRobotData(
            true, robotId, type, status, location, mapName, roomStatus));

        // Verify the data in the database
        mongocxx::client client{mongocxx::uri{testUri}};
        auto db = client[testDbName];
        auto collection = db[activeCollection];

        auto result = collection.find_one(bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("ID", robotId)));
        REQUIRE(result);
        auto view = result->view();

        REQUIRE(view["ID"].get_int32() == robotId);
        REQUIRE(view["Status"].get_utf8().value.to_string() == status);
        REQUIRE(view["Location"].get_int32() == location);
        REQUIRE(view["Map"].get_utf8().value.to_string() == mapName);
        REQUIRE(view["Room Status"].get_utf8().value.to_string() == roomStatus);
    }

    SECTION("Move Robot to Removed Collection") {
        int robotId = 101;

        REQUIRE_NOTHROW(mongoWrapper.moveRobotToRemoved(robotId));

        // Verify that the robot is no longer in the active collection
        mongocxx::client client{mongocxx::uri{testUri}};
        auto db = client[testDbName];
        auto activeColl = db[activeCollection];
        auto removedColl = db[removedCollection];

        auto activeResult = activeColl.find_one(bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("ID", robotId)));
        REQUIRE_FALSE(activeResult);

        // Verify that the robot is in the removed collection
        auto removedResult = removedColl.find_one(bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("ID", robotId)));
        REQUIRE(removedResult);
        auto view = removedResult->view();
        REQUIRE(view["ID"].get_int32() == robotId);
    }
}
