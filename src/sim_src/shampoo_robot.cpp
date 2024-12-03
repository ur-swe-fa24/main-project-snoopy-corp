#include "../../include/sim_lib/shampoo_robot.hpp"
#include <iostream>

    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    ShampooRobot::ShampooRobot(int id) : Robot(RobotType::Shampoo, id) {}
    ShampooRobot::ShampooRobot(int id, float failure_rate) : Robot(RobotType::Shampoo, id, failure_rate) {}

    nlohmann::json ShampooRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Shampoo Level"] = ShampooLevel;
        return json;
    };