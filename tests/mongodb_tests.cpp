#include "database/mongoDBWrapper.hpp"
#include "sim_lib/robot.hpp"
#include "sim_lib/map.hpp"
#include <catch2/catch_test_macros.hpp>
#include <bsoncxx/document/view.hpp>

// Ensure only one instance of mongocxx::instance exists
mongocxx::instance& getMongoInstance() {
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
    const std::string errorLog = "error_log";

    // Create a test MongoDB wrapper
    MongoDBWrapper mongoWrapper(testUri, testDbName, activeCollection, removedCollection, errorLog);

    SECTION("Upsert Robot Data") {
        nlohmann::json roomsEx1 = {
        {"3", {{"Room", "Kitchen"}, {"Cleaning Status", "Unclean"}, {"FloorType", "Wood"}}},
        {"4", {{"Room", "Office"}, {"Cleaning Status", "Clean"}, {"FloorType", "Carpet"}}},
        {"5", {{"Room", "Bathroom"}, {"Cleaning Status", "Clean"}, {"FloorType", "Tile"}}}};
        Map map = Map("TestMap", roomsEx1);
        Robot robo = Robot(RobotType::Scrubber, 101);
        robo.move(5);
        int robotId = 101;
        std::string type = "Scrubber";
        std::string status = "Inactive";
        int location = 5;
        // std::string mapName = "TestMap";
        // std::string roomStatus = "Clean";

        REQUIRE_NOTHROW(mongoWrapper.upsertRobotData(robo.toJson()));

        // Verify the data in the database
        mongocxx::client client{mongocxx::uri{testUri}};
        auto db = client[testDbName];
        auto collection = db[activeCollection];

        auto result = collection.find_one(bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("ID", robotId)));
        REQUIRE(result);
        auto view = result->view();

        REQUIRE(view["ID"].get_int32() == robotId);
        REQUIRE(std::string(view["Status"].get_string().value) == status);
        REQUIRE(view["Location"].get_int32() == location);
        // REQUIRE(std::string(view["Map"].get_string().value) == mapName);
        // REQUIRE(std::string(view["Room Status"].get_string().value) == roomStatus);
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
