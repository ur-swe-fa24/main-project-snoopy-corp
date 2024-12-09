#include "../../include/sim_lib/scrubber_robot.hpp"

    // Constructor with id
    ScrubberRobot::ScrubberRobot(int id) : Robot(RobotType::Scrubber, id) {}

    // Overloaded constructor with id and failure_rate
    ScrubberRobot::ScrubberRobot(int id, float failure_rate) : Robot(RobotType::Scrubber, id, failure_rate) {}

    // Adds water level to the toJson of the parent robot to return a json representation of the scrubber
    nlohmann::json ScrubberRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Water Level"] = WaterLevel;
        return json;
    };