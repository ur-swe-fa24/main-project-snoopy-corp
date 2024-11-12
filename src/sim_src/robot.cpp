#include "../../include/sim_lib/robot.hpp"
#include <iostream>

    // Default constructor 
    Robot::Robot() : type(RobotType::Scrubber), id(-1), queue{} {}

    // Overloaded constructor with type and id parameters
    Robot::Robot(RobotType type, int id) : type(type), id(id), battery_level(10), queue{} {}

    // Overloaded constructor with type, id, and Map parameters
    Robot::Robot(RobotType type, int id, Map currentMap) : type(type), id(id), currentMap(currentMap), battery_level(10), queue{} {}

    float Robot::getEfficiency(){
        return tasks_completed / tasks_attempted;
    }

    int Robot::getId(){
        return id;
    }

    Status Robot::getStatus(){
        return status;
    }

    int Robot::getLocation(){
        return location;
    }

    int Robot::getProgressTask(){
        return progress_task;
    }

    int Robot::getProgressQueue(){
        return progress_queue;
    }

    std::queue<int> Robot::getQueue(){
        return queue;
    }

    int Robot::getBatteryLevel(){
        return battery_level;
    }

    void Robot::update(){
        if(status == Status::Active)
        {
            bool PLACEHOLDER = true;
            if(PLACEHOLDER)    //if(currentMap.GET_ROOM_STATUS(this->getLocation()) == 10)
            {
                if(queue.size() != 0)
                {
                    queue.pop();
                    // for(auto q : queue){
                    //     std::cout << q;
                    // }
                    // if(queue.empty())
                    if(queue.size() == 0)
                        status = Status::Inactive;
                    else
                        move(queue.front());
                }
            }
            else{
                bool successfulClean = clean();
                if(!successfulClean) reportError();
                else battery_level--;
            }
        }
    }


    void Robot::reportError(){
        status = Status::Error;
        // TO BE DETERMINED
    }
    void Robot::move(int room_num){
        location = room_num;
    }

    std::string typeToString(RobotType type){
        switch(type){
            case RobotType::Shampoo: return "Shampoo";
            case RobotType::Scrubber: return "Scrubber";
            case RobotType::Vacuum: return "Vacuum";
            default:          return "Bad typeToString request";
        }
    }

    std::string statusToString(Status status){
        switch(status){
            case Status::Active: return "Active";
            case Status::Inactive: return "Inactive";
            case Status::Error: return "Error";
            default:          return "Bad statusToString request";

        }
    }


    bool Robot::clean(){
        currentMap.updateRoomCleanliness(std::to_string(location), "Clean!");   // WILL BE OVERRIDDEN BY SUBCLASSES
        return true;
    }

    std::string Robot::getMapName(){
        return currentMap.getName();
    }

    std::string Robot::getRoomStatus(){
        return currentMap.getRoomCleanliness(std::to_string(location));
    }
    std::string Robot::toString(){
        std::cout << "ID: " << id << ", Type: " << typeToString(type) 
        << ", Status: " << statusToString(status) << ", Location: " << this->getLocation() 
        << ", Map: " << this->getMapName() << ", Current Room Status: " << this->getRoomStatus() << "\n";
        return "";
    }

    std::string Robot::robotTypeToString(RobotType type) {
        switch (type) {
            case RobotType::Shampoo:
                return "Shampoo";
            case RobotType::Scrubber:
                return "Scrubber";
            case RobotType::Vacuum:
                return "Vacuum";
            default:
                return "Unknown";
        }
    }

    std::string Robot::getRobotTypeFullName(char type) {
        switch (type) {
            case 'S': 
                return "Scrubber";
            case 'H': 
                return "Shampoo";
            case 'V': 
                return "Vacuum";
            default: 
                return "Unknown";
        }
    }

    nlohmann::json Robot::toJson(){
        return nlohmann::json{
            {"ID", id}, 
            {"Type", robotTypeToString(type)}, 
            {"Status", magic_enum::enum_name(type)},
            {"Location", location},
            {"Tasks completed", tasks_completed},
            {"Task attempted", tasks_attempted},
            {"Progress task", progress_task},
            {"Progress Queue", progress_queue},
            {"Battery Level", battery_level},
            {"Queue", queue}};
    }
