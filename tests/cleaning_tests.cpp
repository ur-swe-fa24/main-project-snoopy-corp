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
        {"4", {{"Room", "Bathroom_2"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"5", {{"Room", "Bathroom_3"}, {"Cleaning Status", "-50"}, {"FloorType", "Tile"}}},
        {"6", {{"Room", "DEMO"}, {"Cleaning Status", "-35"}, {"FloorType", "Tile"}}},
        {"7", {{"Room", "DEMO2"}, {"Cleaning Status", "-35"}, {"FloorType", "Tile"}}},
        {"8", {{"Room", "DEMO3"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"9", {{"Room", "DEMO4"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}},
        {"10", {{"Room", "DEMO5"}, {"Cleaning Status", "0"}, {"FloorType", "Tile"}}}


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

    SECTION("Fixing failed robots"){
        VacuumRobot r_6 = VacuumRobot(6, 1);
        s.addRobot(r_6);
        s.getRobot(6)->addTask(4);
        REQUIRE(s.getRobot(6)->getStatus() == Status::Inactive);
        s.update_all();
        REQUIRE(s.getRobot(6)->getStatus() == Status::Active);
        s.update_all();
        REQUIRE(s.getRobot(6)->getStatus() == Status::Error);
        REQUIRE(s.getRobot(6)->getBatteryLevel() == 59);
        s.fixRobot(6);
        REQUIRE(s.getRobot(6)->getStatus() == Status::BeingFixed);
        REQUIRE(s.getRobot(6)->getBatteryLevel() == 60);
        REQUIRE(s.getRobot(6)->getPauseTicks() == 10);
        for(int i = 0; i < 51; i++) {s.update_all();}
        REQUIRE(s.getRobot(6)->getStatus() == Status::Inactive);

        VacuumRobot r_7 = VacuumRobot(7,0);
        s.addRobot(r_7);
        s.getRobot(7)->addTask(5);

        // REQUIRE(stoi(s.getSelectedMap().getRoomCleanliness("5")) == 0);
        for(int i = 0; i < 62; i++){
            s.update_all();
        }
        REQUIRE(stoi(s.getSelectedMap().getRoomCleanliness("5")) == 10);

        VacuumRobot r_8 = VacuumRobot(8, 0);
        s.addRobot(r_8);
        s.getRobot(8)->addTask(6);
        for(int i = 0; i < 80; i++){
            s.update_all();
        }
        s.getRobot(8)->addTask(7);
        for(int i = 0; i < 62; i++){
            s.update_all();
        }
        REQUIRE(s.getRobot(8)->getStatus() == Status::Inactive);

    }

    SECTION("Tasks completed and attempted metrics"){
        VacuumRobot r_9 = VacuumRobot(9, 0);
        s.addRobot(r_9);
        s.getRobot(9)->addTask(8);
        s.getRobot(9)->addTask(9);
        REQUIRE(s.getRobot(9)->getEfficiency() == 0);
        for(int i = 0; i < 15; i++){
            s.update_all();
        }
        REQUIRE(s.getRobot(9)->getTA() == 2);
        REQUIRE(s.getRobot(9)->getTC() == 1);

        REQUIRE(s.getRobot(9)->getEfficiency() == Catch::Approx(0.5));
    }

    SECTION("Robots fail when no battery at the location"){
        VacuumRobot r_fail = VacuumRobot(10, 1.0);
        r_fail.setBatteryLevel(2);
        s.addRobot(r_fail);
        s.getRobot(r_fail.getId())->addTask(1);
        s.update_all();
        REQUIRE(s.getRobot(10)->getLocation() == 1);
        REQUIRE(s.getRobot(10)->getStatus() == Status::Active); 
        s.update_all();
        REQUIRE(s.getRobot(10)->getLocation() == 1);
        REQUIRE(s.getRobot(10)->getStatus() == Status::Error);    
    }

}