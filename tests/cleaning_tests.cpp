#define CATCH_CONFIG_MAIN
#include "sim_lib/_sim_lib.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_approx.hpp>
#include <iostream>
#include <string>

TEST_CASE("Cleaning Unit Tests") {
    json roomsEx0 = {
        {"1", {{"Room", "Kitchen"}, {"Cleaning Status", "0"}, {"FloorType", "Wood"}}},
        {"2", {{"Room", "Office"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}}
    };
    Map m1 = Map("m1", roomsEx0);

    ScrubberRobot r1 = ScrubberRobot(0, m1);
    ShampooRobot r2 = ShampooRobot(1, m1);
    VacuumRobot r3 = VacuumRobot(2, m1);

    r1.addTask(1);
    r1.addTask(3);
    r2.addTask(2);

    SECTION("Robot has initial room"){
        REQUIRE(r1.getLocation() == -1);
        r1.update();
        REQUIRE(r1.getLocation() == 1);
        r1.update();
        REQUIRE(r1.getLocation() == 1);
    }

    SECTION("Room is being properly cleaned"){
        r2.update(); // move to room
        REQUIRE(stoi(m1.getRoomCleanliness("2")) == 0);
        r2.update(); // clean room

        
        REQUIRE(stoi(r2.getMap().getRoomCleanliness(std::to_string(r2.getLocation())))==1);
        REQUIRE(stoi(m1.getRoomCleanliness("2")) == 1);
        for(int i = 0; i < 9; i++){
            r2.update();
        }
        r2.update();
        REQUIRE(stoi(m1.getRoomCleanliness("2")) == 10);
        REQUIRE(r2.getStatus() == Status::Inactive);
    }

    SECTION("Robot is completing a sequence of tasks"){
       
        for(int i = 0; i < 12; i++){
            r1.update();
        }
        REQUIRE(r1.getLocation() == 3);
        REQUIRE(stoi(m1.getRoomCleanliness("1")) == 10);
        REQUIRE(stoi(m1.getRoomCleanliness("3")) == 0);


    }

}