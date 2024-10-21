#include "../../include/sim_lib/robot.hpp"
#include <iostream>

    // Default constructor 
    Robot::Robot() : type(RobotType::Scrubber), id(-1), currentMap(0) {}

    // Overloaded constructor with type and id parameters
    Robot::Robot(RobotType type, int id, int currentMap) : type(type), id(id), currentMap(currentMap), battery_level(10) {}

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

    std::vector<int> Robot::getQueue(){
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
                queue.erase(queue.begin());
                if(queue.empty())
                    status = Status::Inactive;
                else
                    move(queue.front());
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
        return true;
    }
    std::string Robot::toString(){
        std::cout << "ID: " << id << ", Type: " << typeToString(type) << ", Status: " << statusToString(status) << "\n";
        return "";
    }