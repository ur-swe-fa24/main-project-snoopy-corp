#include "../../include/sim_lib/vacuum_robot.hpp"

    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    VacuumRobot::VacuumRobot(int id, Map currentMap) : Robot(RobotType::Vacuum, id, currentMap) {}
    VacuumRobot::VacuumRobot(int id) : Robot(RobotType::Vacuum, id) {}

    bool VacuumRobot::clean() 
    {
        bool PLACEHOLDER = true;
        // generate random number for error
        if(!PLACEHOLDER)   //if error
        {
            return false;
        }

        currentMap.updateRoomCleanliness(std::to_string(location), "Clean!");   // toy demo
        return true;    
    }