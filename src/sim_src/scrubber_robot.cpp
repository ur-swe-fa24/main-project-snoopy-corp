#include "../../include/sim_lib/scrubber_robot.hpp"
#include <string>
#include <iostream>
#include <random>

    

    // Overloaded constructor with id and map parameters
    ScrubberRobot::ScrubberRobot(int id, Map& currentMap) : Robot(RobotType::Scrubber, id, currentMap) {}

    ScrubberRobot::ScrubberRobot(int id, Map& currentMap, float failure_rate) : Robot(RobotType::Scrubber, id, currentMap, failure_rate) {}


    bool ScrubberRobot::clean() 
    {
        bool PLACEHOLDER = true;
        // std::cout << "proper clean called";

        // generate random number for error
        if(!PLACEHOLDER)   //if error
        {
            return false;
        }
        if(PLACEHOLDER) //if(currentMap[location].type == Map::Wood || currentMap[location].type == Map::Tile)
        {
            int current_cleanliness = stoi(currentMap.getRoomCleanliness(std::to_string(location)));
            // std::cout << "before: " << current_cleanliness;
            current_cleanliness++;
            // std::cout << "after: " << current_cleanliness;
            currentMap.updateRoomCleanliness(std::to_string(location), std::to_string(current_cleanliness));
            // std::cout << "after fr: " << currentMap.getRoomCleanliness(std::to_string(location));
            WaterLevel--;
        }
        return true;    
    }

    nlohmann::json ScrubberRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Water Level"] = WaterLevel;
        return json;
    };