#include "../../include/sim_lib/scrubber_robot.hpp"

    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    ScrubberRobot::ScrubberRobot(int id, int currentMap) : Robot(RobotType::Scrubber, id, currentMap) {}

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
            // currentMap[location].status ++
            WaterLevel--;
        }
        return true;    
    }