#include "../../include/sim_lib/shampoo_robot.hpp"
#include <iostream>

    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    ShampooRobot::ShampooRobot(int id, Map& currentMap) : Robot(RobotType::Shampoo, id, currentMap) {}
    ShampooRobot::ShampooRobot(int id, Map& currentMap, float failure_rate) : Robot(RobotType::Shampoo, id, currentMap, failure_rate) {}


    bool ShampooRobot::clean() 
    {
        bool PLACEHOLDER = true;
        // generate random number for error
        if(!PLACEHOLDER)   //if error
        {
            return false;
        }
        if(PLACEHOLDER) //if(currentMap[location].type == Map::Carpet || currentMap[location].type == Map::Carpet)
        {
            int current_cleanliness = stoi(currentMap.getRoomCleanliness(std::to_string(location)));
            // std::cout << "before: " << current_cleanliness;
            current_cleanliness++;
            // std::cout << "after: " << current_cleanliness;
            currentMap.updateRoomCleanliness(std::to_string(location), std::to_string(current_cleanliness));
            // std::cout << "after fr: " << currentMap.getRoomCleanliness(std::to_string(location));           
            ShampooLevel--;
        }
        return true;    
    }