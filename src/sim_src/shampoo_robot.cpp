#include "../../include/sim_lib/shampoo_robot.hpp"

    // Constructor with id
    ShampooRobot::ShampooRobot(int id) : Robot(RobotType::Shampoo, id) {}

    // Overloaded constructor with id and failure_rate
    ShampooRobot::ShampooRobot(int id, float failure_rate) : Robot(RobotType::Shampoo, id, failure_rate) {}

    // Adds shampoo level to the toJson of the parent robot to return a json representation of the shampoo
    nlohmann::json ShampooRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Shampoo Level"] = ShampooLevel;
        return json;
    };