#include "../../include/sim_lib/vacuum_robot.hpp"

    // Constructor with id
    VacuumRobot::VacuumRobot(int id) : Robot(RobotType::Vacuum, id) {}

    // Overloaded constructor with id and failure_rate
    VacuumRobot::VacuumRobot(int id, float failure_rate) : Robot(RobotType::Vacuum, id, failure_rate) {}

    // Adds trash bag level to the toJson of the parent robot to return a json representation of the vacuum
    nlohmann::json VacuumRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Trash Bag Level"] = TrashbagLevel;
        return json;
    };