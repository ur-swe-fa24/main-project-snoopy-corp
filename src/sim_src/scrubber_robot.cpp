#include "../../include/sim_lib/scrubber_robot.hpp"
#include <string>
#include <iostream>

    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    ScrubberRobot::ScrubberRobot(int id, Map& currentMap) : Robot(RobotType::Scrubber, id, currentMap) {}

    // ScrubberRobot::ScrubberRobot(int id) : Robot(RobotType::Scrubber, id) {}

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