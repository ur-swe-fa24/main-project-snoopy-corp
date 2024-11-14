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
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"4", {{"Room", "Bathroom_2"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}}
    };
    Map m1 = Map("m1", roomsEx0);

    ScrubberRobot r1 = ScrubberRobot(0, m1, 0);
    ShampooRobot r2 = ShampooRobot(1, m1, 0);
    VacuumRobot r3 = VacuumRobot(2, m1, 0);

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

    SECTION("Robots fail when intended"){
        VacuumRobot r_fail = VacuumRobot(3, m1, 1.0);
        r_fail.addTask(1);
        r_fail.update();
        REQUIRE(r_fail.getLocation() == 1);
        r_fail.update();
        REQUIRE(r_fail.getStatus() == Status::Error);

        VacuumRobot r_fail_50 = VacuumRobot(4, m1, 0.5);
        r_fail_50.addTask(2);
        r_fail_50.addTask(3);
        for(int i = 0; i < 21; i++){
            r_fail_50.update();
        }
        REQUIRE(r_fail_50.getStatus() == Status::Error);    // this technically has a 0.0000009% chance of failing so should probably be removed
                                                            // but I wanted to test that a conditionally failing robot may fail

        VacuumRobot r_succeed = VacuumRobot(5, m1, 0);
        r_succeed.addTask(4);
        for(int i = 0; i < 15; i++){
            r_succeed.update();
        }
        REQUIRE(r_succeed.getStatus() == Status::Inactive);    
    }

    SECTION("Ensure fail rates are correctly generated"){
        VacuumRobot r_4 = VacuumRobot(6,m1);
        std::cout << r_4.getFailRate();
        bool valid = r_4.getFailRate() <= 0.01 || r_4.getFailRate() == Catch::Approx(0.1);
        REQUIRE(valid);
    }

}