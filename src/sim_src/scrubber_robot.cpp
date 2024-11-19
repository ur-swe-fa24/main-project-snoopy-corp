#include "../../include/sim_lib/scrubber_robot.hpp"
#include <string>
#include <iostream>
#include <random>

    

    // Overloaded constructor with id and map parameters
    ScrubberRobot::ScrubberRobot(int id) : Robot(RobotType::Scrubber, id) {}

    ScrubberRobot::ScrubberRobot(int id, float failure_rate) : Robot(RobotType::Scrubber, id, failure_rate) {}


    bool ScrubberRobot::clean() 
    {
        if(getRandom() <= failure_rate){
            return false;
        }
        else{
            
            return true;    
        }    
    }

    nlohmann::json ScrubberRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Water Level"] = WaterLevel;
        return json;
    };