#include "../../include/sim_lib/vacuum_robot.hpp"

    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    VacuumRobot::VacuumRobot(int id, int currentMap) : Robot(RobotType::Vacuum, id, currentMap) {}

    bool VacuumRobot::clean() 
    {
        bool PLACEHOLDER = true;
        // generate random number for error
        if(PLACEHOLDER)   //if error
        {
            return false;
        }

        // currentMap[location].status ++
        return true;    
    }