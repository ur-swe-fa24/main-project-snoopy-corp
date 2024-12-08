#include "../../include/sim_lib/vacuum_robot.hpp"
// #include <random>
    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    VacuumRobot::VacuumRobot(int id) : Robot(RobotType::Vacuum, id) {}
    VacuumRobot::VacuumRobot(int id, float failure_rate) : Robot(RobotType::Vacuum, id, failure_rate) {}


    nlohmann::json VacuumRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Trash Bag Level"] = TrashbagLevel;
        return json;
    };