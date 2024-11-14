#include "../../include/sim_lib/vacuum_robot.hpp"
// #include <random>
    // Default constructor 
    // ScrubberRobot::ScrubberRobot() :  Robot(RobotType::Generic, 0, 0) {}

    // Overloaded constructor with type and id parameters
    VacuumRobot::VacuumRobot(int id, Map& currentMap) : Robot(RobotType::Vacuum, id, currentMap) {}
    VacuumRobot::VacuumRobot(int id, Map& currentMap, float failure_rate) : Robot(RobotType::Vacuum, id, currentMap, failure_rate) {}

    bool VacuumRobot::clean() 
    {
        if(getRandom() <= failure_rate){
            return false;
        }
        else{
            int current_cleanliness = stoi(currentMap.getRoomCleanliness(std::to_string(location)));
            current_cleanliness++;
            currentMap.updateRoomCleanliness(std::to_string(location), std::to_string(current_cleanliness));
        return true;    
        }
    }

    nlohmann::json VacuumRobot::toJson() {
        nlohmann::json json = Robot::toJson();
        json["Trash Bag Level"] = TrashbagLevel;
        return json;
    };