#include "../../include/sim_lib/shampoo_robot.hpp"

    // Constructor with id
    ShampooRobot::ShampooRobot(int id) : Robot(RobotType::Shampoo, id), ShampooLevel(15) {}

    // Overloaded constructor with id and failure_rate
    ShampooRobot::ShampooRobot(int id, float failure_rate) : Robot(RobotType::Shampoo, id, failure_rate), ShampooLevel(15) {}

    // Adds shampoo level to the toJson of the parent robot to return a json representation of the shampoo
    nlohmann::json ShampooRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Special"] = {{"Shampoo Level", ShampooLevel}};
        return json;
    };

    bool ShampooRobot::decrementBatteryLevel(int amt) {  
        ShampooLevel -= 1;
        if (ShampooLevel < 0) {
            err_message = "Robot ran out of Shampoo";
            ShampooLevel = 0;
            return false;
        }
        return Robot::decrementBatteryLevel(amt);
    };