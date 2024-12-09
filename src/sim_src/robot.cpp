#include "../../include/sim_lib/robot.hpp"
#include <iostream>
using json = nlohmann::json;


    // Default constructor 
    Robot::Robot() : battery_level(60), queue{}, status(Status::Inactive), location(-1),
    gen(std::random_device{}()), float_distribution(0, 1), fail_distribution(0, 0.005) {}

    // Overloaded constructor with type, id parameters
    Robot::Robot(RobotType type, int id) : type(type), id(id), battery_level(60), queue{}, status(Status::Inactive), location(-1),
    gen(std::random_device{}()), float_distribution(0, 1), fail_distribution(0, 0.005) {
        failure_rate = genFailRate();   // robots by default will have a 0-0.5% chance of failing on a given task segment (10 per room)
        if(failure_rate > 0.00495)    failure_rate = 0.1;     //robots have a 1% chance of being defective
    }
    
    // Overloaded constructor with type, id, failure_rate parameters
    Robot::Robot(RobotType type, int id, float failure_rate) : type(type), id(id), battery_level(60), queue{}, 
    status(Status::Inactive), location(-1), gen(std::random_device{}()), float_distribution(0, 1), failure_rate(failure_rate) {}


    // Get efficiency of robot as tasks completed over tasks attempted
    float Robot::getEfficiency(){
        if(tasks_attempted > 0){
            float efficiency = (float) tasks_completed / tasks_attempted;
            return efficiency;
        }
        else return 0;
    }

    // Get ID for the robot
    int Robot::getId() const{
        return id;
    }

    // Get Status of the robot
    Status Robot::getStatus(){
        return status;
    }

    // Get Locaiton of the robot
    int Robot::getLocation(){
        return location;
    }

    // Get the current in-work task of the robot
    int Robot::getProgressTask(){
        return progress_task;
    }

    // Clear the queue of tasks of the robot
    void Robot::clearQueue(){
        while (!queue.empty()) {
            queue.pop();
        }
    }

    // Get ID for the robot
    int Robot::getProgressQueue(){
        return progress_queue;
    }

    // Get the queue of robot tasks
    std::queue<int> Robot::getQueue(){
        return queue;
    }

    // Return the next task in the queue
    void Robot::popQueue(){
        queue.pop();
    }

    // Get the battery level of the robot
    int Robot::getBatteryLevel(){
        return battery_level;
    }

    // Decrease the battery of the robot by given amount and error if battery goes below 0
    bool Robot::decrementBatteryLevel(int amt){
        battery_level -= amt;
        if (battery_level < 0) {
            err_message = "Robot Battery Died";
            battery_level = 0;
            return false;
        }
        return true;
    }

    // Generate a random float based on the distribution
    float Robot::getRandom(){
        return float_distribution(gen);
    }

    // Generate a failure float given the distribution 
    float Robot::genFailRate(){
        return fail_distribution(gen);
    }

    // Add a task to the robot's task queue
    void Robot::addTask(int room){
        queue.push(room);
        return;
    }

    // Add a task of multiple rooms to the robot
    void Robot::addTask(std::vector<int> rooms){
        for(int e : rooms){
            queue.push(e);
        }
        return;
    }

    // Set the status of the robot to one of Status's enum value
    void Robot::setStatus(Status s){
        status = s;
        return;
    }

    // Create and return a Json with the id and the location for error while setting status to error
    nlohmann::json Robot::reportError(){
        status = Status::Error;
        return json{{"ID", id},
                    {"Location", location},
                    {"ErrorNotes", err_message}};
    }

    // Move the robot's location to given room number
    void Robot::move(int room_num) {
        location = room_num;
    }

    // Change the robot's type to string using magic enum
    std::string Robot::typeToString(RobotType Robot_type){
        return std::string(magic_enum::enum_name(Robot_type));
    }

    // Change the robot's status to string using magic enum
    std::string Robot::statusToString(Status status){
        return std::string(magic_enum::enum_name(status));
    }

    // Attempt robot cleaning with a random chance of failiure
    bool Robot::clean(){
        if(getRandom() <= failure_rate){
            int choice = rand() % 2;
            switch(choice){
                case 1:
                    err_message = "Cannot clean room due to Robot Damage";
                default:
                    err_message = "Cannot clean room due to Sensor Error";
            }
            return false;
        }
        else
            return true;    
    
    }

    // Provide a string representation of the Robot Data
    std::string Robot::toString(){
        std::cout << "ID: " << id << ", Type: " << this->typeToString(type) 
        << ", Status: " << this->statusToString(status) << ", Location: " << this->getLocation();
        // << ", Map: " << this->getMapName() << ", Current Room Status: " << this->getRoomStatus() << "\n";
        return "";
    }

    // Gets the Full Name of a Robot based on input character
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

    // Sets the robot ID
    void Robot::setId(int newId) {
        id = newId;
    }

    // Convert the Robot to JSON with all of its member values
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
            {"Queue Length", queue.size()}, //Time remaining
            {"Task attempted", tasks_attempted},
            {"Progress task", progress_task},
            {"Progress Queue", progress_queue},
            {"Battery Level", battery_level},
            {"Tasks completed", tasks_completed},
            {"Efficiency", this->getEfficiency()},
            {"Queue", vec}};
        return j;
    }


 

