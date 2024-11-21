#define CATCH_CONFIG_MAIN
#include "sim_lib/_sim_lib.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_approx.hpp>
#include <iostream>
#include <string>
#include <queue>

TEST_CASE("Cleaning Unit Tests") {
    json roomsEx0 = {
        {"1", {{"Room", "Kitchen"}, {"Cleaning Status", "0"}, {"FloorType", "Wood"}}},
        {"2", {{"Room", "Office"}, {"Cleaning Status", "0"}, {"FloorType", "Carpet"}}},
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"4", {{"Room", "Bathroom_2"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}}
    };
    Map m1 = Map("m1", roomsEx0);

    ScrubberRobot r1 = ScrubberRobot(0, 0);
    ShampooRobot r2 = ShampooRobot(1, 0);
    VacuumRobot r3 = VacuumRobot(2, 0);

    SimulationDriver s = SimulationDriver(m1);

    s.addRobot(r1);
    s.addRobot(r2);
    s.addRobot(r3);
    
        s.getRobot(0)->addTask(1);
        std::queue q = s.getRobot(0)->getQueue();
        // std::cout << "Front: " << q.front() << "\n";
        s.getRobot(0)->addTask(3);
        s.getRobot(1)->addTask(2);

    SECTION("Robot has initial room"){
        REQUIRE(s.getRobot(0)->getLocation() == -1);
        s.update_all();
        REQUIRE(s.getRobot(0)->getLocation() == 1);
    }

    SECTION("Room is being properly cleaned"){
        s.update_all(); // move to room
        REQUIRE(stoi(m1.getRoomCleanliness("2")) == 0);
        s.update_all(); // clean room


        REQUIRE(stoi(s.getSelectedMap().getRoomCleanliness(std::to_string(s.getRobot(1)->getLocation())))==1);
        REQUIRE(stoi(s.getSelectedMap().getRoomCleanliness("2")) == 1);
        for(int i = 0; i < 9; i++){
            s.update_all();
        }
        REQUIRE(stoi(s.getSelectedMap().getRoomCleanliness("2")) == 10);
        REQUIRE(r2.getStatus() == Status::Inactive);
    }

    SECTION("Robot is completing a sequence of tasks"){
       
        for(int i = 0; i < 12; i++){
            s.update_all();
        }
        REQUIRE(s.getRobot(0)->getLocation() == 3);
        REQUIRE(stoi(s.getSelectedMap().getRoomCleanliness("1")) == 10);
        REQUIRE(stoi(s.getSelectedMap().getRoomCleanliness("3")) == 0);
    }

    SECTION("Robots fail when intended"){
        VacuumRobot r_fail = VacuumRobot(3, 1.0);
        s.addRobot(r_fail);
        s.getRobot(r_fail.getId())->addTask(1);
        s.update_all();
        REQUIRE(s.getRobot(3)->getLocation() == 1);
        s.update_all();
        REQUIRE(s.getRobot(3)->getStatus() == Status::Error);

        VacuumRobot r_succeed = VacuumRobot(4, 0);
        s.addRobot(r_succeed);
        s.getRobot(r_succeed.getId())->addTask(4);
        for(int i = 0; i < 15; i++){
            s.update_all();
        }
        REQUIRE(s.getRobot(4)->getStatus() == Status::Inactive);    
    }

    SECTION("Ensure fail rates are correctly generated"){
        VacuumRobot r_5 = VacuumRobot(5);
        s.addRobot(r_5);
        std::cout << s.getRobot(5)->getFailRate();
        bool valid = s.getRobot(5)->getFailRate() <= 0.01 || s.getRobot(5)->getFailRate() == Catch::Approx(0.1);
        REQUIRE(valid);
    }

}