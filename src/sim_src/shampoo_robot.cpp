#include "../../include/sim_lib/shampoo_robot.hpp"

    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    ShampooRobot::ShampooRobot(int id, Map currentMap) : Robot(RobotType::Shampoo, id, currentMap) {}
    ShampooRobot::ShampooRobot(int id) : Robot(RobotType::Shampoo, id) {}

    bool ShampooRobot::clean() 
    {
        bool PLACEHOLDER = true;
        // generate random number for error
        if(PLACEHOLDER)   //if error
        {
            return false;
        }
        if(PLACEHOLDER) //if(currentMap[location].type == Map::Carpet || currentMap[location].type == Map::Carpet)
        {
            currentMap.updateRoomCleanliness(std::to_string(location), "Clean!");   // toy demo
            ShampooLevel--;
        }
        return true;    
    }