#include "../../include/sim_lib/vacuum_robot.hpp"

    // Constructor with id
    VacuumRobot::VacuumRobot(int id) : Robot(RobotType::Vacuum, id), TrashbagLevel(0) {}

    // Overloaded constructor with id and failure_rate
    VacuumRobot::VacuumRobot(int id, float failure_rate) : Robot(RobotType::Vacuum, id, failure_rate), TrashbagLevel(0) {}

    // Adds trash bag level to the toJson of the parent robot to return a json representation of the vacuum
    nlohmann::json VacuumRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Special"] = {{"Trash Bag Level", TrashbagLevel}};
        return json;
    };

    bool VacuumRobot::decrementBatteryLevel(int amt) {  
        TrashbagLevel += 1;
        if (TrashbagLevel > 15) {
            err_message = "Robot's Trash Bag is full";
            TrashbagLevel = 0;
            return false;
        }
        return Robot::decrementBatteryLevel(amt);
    };