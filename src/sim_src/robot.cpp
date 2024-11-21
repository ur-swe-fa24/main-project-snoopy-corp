#include "../../include/sim_lib/robot.hpp"
#include <iostream>
using json = nlohmann::json;


    // // Default constructor 
    //initial value of reference to non-const must be an lvalueC/C++(461)
    // Robot::Robot() : currentMap(Map("DEFAULT_MAP", {{"-1", {{"Room", "DEFAULT"}, {"Cleaning Status", "-1"}, {"FloorType", "DEFAULT"}}}})){}


    Robot::Robot() : battery_level(10), queue{}, status(Status::Inactive), location(-1),
    gen(std::random_device{}()), float_distribution(0, 1), fail_distribution(0, 0.005) {}

    // Overloaded constructor with type, id, and Map parameters
    Robot::Robot(RobotType type, int id) : type(type), id(id), battery_level(10), queue{}, status(Status::Inactive), location(-1),
    gen(std::random_device{}()), float_distribution(0, 1), fail_distribution(0, 0.005) {
        failure_rate = genFailRate();   // robots by default will have a 0-0.5% chance of failing on a given task segment (10 per room)
        if(failure_rate > 0.00495)    failure_rate = 0.1;     //robots have a 1% chance of being defective
    }

    Robot::Robot(RobotType type, int id, float failure_rate) : type(type), id(id), battery_level(10), queue{}, 
    status(Status::Inactive), location(-1), gen(std::random_device{}()), float_distribution(0, 1), failure_rate(failure_rate) {}

    // Robot::Robot(const Robot& other) : currentMap(other.currentMap){}

    // Robot& Robot::operator=(Robot&& other){
    //     int id = std::move(other.id);
    //     return *this;
    // }


    float Robot::getEfficiency(){
        return tasks_completed / tasks_attempted;
    }

    int Robot::getId() const{
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

    void Robot::popQueue(){
        queue.pop();
    }

    int Robot::getBatteryLevel(){
        return battery_level;
    }

    void Robot::setBatteryLevel(int amt){
        battery_level -= amt;
    }
    float Robot::getRandom(){
        return float_distribution(gen);
    }

    float Robot::genFailRate(){
        return fail_distribution(gen);
    }
    void Robot::addTask(int room){
        queue.push(room);
        return;
    }

    void Robot::setStatus(Status s){
        status = s;
        return;
    }

    void Robot::update(){
        // std::cout << "update called ";
        // if(status == Status::Inactive)
        // {
        //     if(queue.size() != 0)
        //     {
        //         move(queue.front());
        //         setStatus(Status::Active);
        //     }
        // }
        // else if(status == Status::Active)
        // {
        //     if(std::stoi(currentMap.getRoomCleanliness(std::to_string(location))) >= 10)    //if(currentMap.GET_ROOM_STATUS(this->getLocation()) == 10)
        //     {
        //         if(queue.size() != 0)
        //         {
        //             queue.pop();
        //             if(queue.size() == 0)
        //                 status = Status::Inactive;
        //             else
        //                 move(queue.front());
        //         }
        //     }
        //     else{
        //         // std::cout << "clean about to be called; ";
        //         bool successfulClean = clean();
        //         if(!successfulClean) reportError();
        //         else battery_level--;
        //     }
        // }
        // //else: error case
    }


    void Robot::reportError(){
        status = Status::Error;
        // TO BE DETERMINED
    }

    void Robot::move(int room_num) {
        location = room_num;
    }

    std::string Robot::typeToString(RobotType Robot_type){
        return std::string(magic_enum::enum_name(Robot_type));
    }

    std::string Robot::statusToString(Status status){
        return std::string(magic_enum::enum_name(status));
    }


    bool Robot::clean(){
        if(getRandom() <= failure_rate){
            return false;
        }
        else
            return true;    
    
    }


    std::string Robot::toString(){
        std::cout << "ID: " << id << ", Type: " << this->typeToString(type) 
        << ", Status: " << this->statusToString(status) << ", Location: " << this->getLocation();
        // << ", Map: " << this->getMapName() << ", Current Room Status: " << this->getRoomStatus() << "\n";
        return "";
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

    void Robot::setId(int newId) {
        id = newId;
    }

    nlohmann::json Robot::toJson(){
        std::vector<int> vec;
        std::queue<int> tempQueue = queue;
        while (!tempQueue.empty()) {
            vec.push_back(tempQueue.front());
            tempQueue.pop();
        }
        auto j = json{
            {"ID", id}, 
            {"Type", std::string(magic_enum::enum_name(type))}, 
            {"Status", std::string(magic_enum::enum_name(status))},
            // {"Map", currentMap.getName()},
            {"Location", location},
            // {"Room Status", getRoomStatus()},
            {"Tasks completed", tasks_completed},
            {"Task attempted", tasks_attempted},
            {"Progress task", progress_task},
            {"Progress Queue", progress_queue},
            {"Battery Level", battery_level},
            {"Queue", vec}};
        return j;
    }
 

