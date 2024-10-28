#include "../../include/sim_lib/scrubber_robot.hpp"
#include <string>

    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    ScrubberRobot::ScrubberRobot(int id, Map currentMap) : Robot(RobotType::Scrubber, id, currentMap) {}

    ScrubberRobot::ScrubberRobot(int id) : Robot(RobotType::Scrubber, id) {}

    bool ScrubberRobot::clean() 
    {
        bool PLACEHOLDER = true;
        // generate random number for error
        if(PLACEHOLDER)   //if error
        {
            return false;
        }
        if(PLACEHOLDER) //if(currentMap[location].type == Map::Wood || currentMap[location].type == Map::Tile)
        {
            currentMap.updateRoomCleanliness(std::to_string(location), "Clean!");   // toy demo
            WaterLevel--;
        }
        return true;    
    }