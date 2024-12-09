#define CATCH_CONFIG_MAIN
#include "sim_lib/_sim_lib.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Cleaning Unit Tests") {

    json rooms = {
        {"1", {{"Room", "Kitchen"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"2", {{"Room", "Office"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"4", {{"Room", "Bathroom_2"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"5", {{"Room", "Bathroom_3"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"6", {{"Room", "PoolHouse"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"7", {{"Room", "Basement"}, {"Cleaning Status", "0"}, {"FloorType", "Wood"}}},
        {"8", {{"Room", "LivingRom"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"9", {{"Room", "Bedroom1"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"10", {{"Room", "Bedroom2"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"11", {{"Room", "Study"}, {"Cleaning Status", "0"}, {"FloorType", "Wood"}}},
        {"12", {{"Room", "GameRoom"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"13", {{"Room", "Bedroom3"}, {"Cleaning Status", "0"}, {"FloorType", "Wood"}}}

    };

    Map m1 = Map("m1", rooms);
    SimulationDriver s = SimulationDriver(m1);
    SimulationDriver t = SimulationDriver(m1);

    VacuumRobot v0 = VacuumRobot(0,0);
    VacuumRobot v1 = VacuumRobot(1,0);
    ScrubberRobot c2 = ScrubberRobot(2,0);
    ScrubberRobot c3 = ScrubberRobot(3,0);
    ShampooRobot h4 = ShampooRobot(4,0);
    ShampooRobot h5 = ShampooRobot(5,0);

    s.addRobot(v0);
    s.addRobot(v1);
    s.addRobot(c2);
    s.addRobot(c3);
    s.addRobot(h4);

    t.addRobot(h5);
    // s.addRobot(h5);
    SECTION("Robots Assigned Correctly"){
        s.assignmentModule({1,2,3,4,5,6,7,8,9,10,11,12});
        REQUIRE(s.getRobot(0)->timeRemaining() >= 20);
    }

    SECTION("Rooms Cleaned Correctly"){
        s.assignmentModule({1,2,3,4,5,6,7,8,9,10,11,12});
        for(int i = 0; i < 25; i++)
        {
            s.update_all();
        }
        REQUIRE(s.getSelectedMap().getRoomCleanliness("1") == "10");
        REQUIRE(s.getSelectedMap().getRoomCleanliness("5") == "10");
    }

    SECTION("Uncleanable rooms not assigned"){
        int s_size = s.assignmentModule({1,2,3,4,5,6,7,8,9,10,11,12,13}).size();
        REQUIRE(s_size == 0);

        int t_size = t.assignmentModule({1,2,3,4,5,6,7,8,9,10,11,12,13}).size();
        REQUIRE(t_size == 8);
    }

    SECTION("Same room multiple times"){
        t.assignmentModule({2,2,2,2});
        REQUIRE(t.getRobot(5)->timeRemaining() == 10);

        s.assignmentModule({3,3,3,3});
        REQUIRE(s.getRobot(0)->timeRemaining() == 10);
        REQUIRE(s.getRobot(1)->timeRemaining() == 0);

    }


}