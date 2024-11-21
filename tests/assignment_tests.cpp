#define CATCH_CONFIG_MAIN
#include "sim_lib/_sim_lib.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_approx.hpp>
#include <iostream>
#include <string>
#include <queue>

TEST_CASE("Cleaning Unit Tests") {

    json rooms = {
        {"1", {{"Room", "Kitchen"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"2", {{"Room", "Office"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"4", {{"Room", "Bathroom_2"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"5", {{"Room", "Bathroom_3"}, {"Cleaning Status", "-50"}, {"FloorType", "Tile"}}},
        {"6", {{"Room", "PoolHouse"}, {"Cleaning Status", "-35"}, {"FloorType", "Tile"}}},
        {"7", {{"Room", "Basement"}, {"Cleaning Status", "-35"}, {"FloorType", "Wood"}}},
        {"8", {{"Room", "LivingRom"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"9", {{"Room", "Bedroom1"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"10", {{"Room", "Bedroom2"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"11", {{"Room", "Study"}, {"Cleaning Status", "0"}, {"FloorType", "Wood"}}},
        {"12", {{"Room", "GameRoom"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"13", {{"Room", "Bedroom3"}, {"Cleaning Status", "0"}, {"FloorType", "Wood"}}}

    };

    Map m1 = Map("m1", rooms);
    SimulationDriver s = SimulationDriver(m1);

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
    // s.addRobot(h5);
    SECTION(""){
        s.assignmentModule({1,2,3,4,5,6,7,8,9,10,11,12});
        REQUIRE(s.getRobot(0)->timeRemaining() >= 20);
    }

}