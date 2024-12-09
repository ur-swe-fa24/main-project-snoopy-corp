#include "../../include/sim_lib/scrubber_robot.hpp"

    // Constructor with id
    ScrubberRobot::ScrubberRobot(int id) : Robot(RobotType::Scrubber, id), WaterLevel(15) {}

    // Overloaded constructor with id and failure_rate
    ScrubberRobot::ScrubberRobot(int id, float failure_rate) : Robot(RobotType::Scrubber, id, failure_rate), WaterLevel(15) {}

    // Adds water level to the toJson of the parent robot to return a json representation of the scrubber
    nlohmann::json ScrubberRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Water Level"] = WaterLevel;
        json["Special"] = {{"Water Level", WaterLevel}};
        return json;
    };

    bool ScrubberRobot::decrementBatteryLevel(int amt) {  
        WaterLevel -= 1;
        if (WaterLevel < 0) {
            err_message = "Robot ran out of Water";
            WaterLevel = 0;
            return false;
        }
        return Robot::decrementBatteryLevel(amt);
    };