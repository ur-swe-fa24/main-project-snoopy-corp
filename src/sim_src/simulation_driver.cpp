#include "../../include/sim_lib/simulation_driver.hpp"
#include <ostream>
#include <pthread.h>
#include <iostream>
#include <magic_enum.hpp>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <set>


    // Default constructor that sets mongo to null, start time, and initializes thread lock
    SimulationDriver::SimulationDriver() : mongo_wrapper(std::nullopt), start(std::chrono::system_clock::now()){
        if (pthread_rwlock_init(&robotsLock, nullptr) != 0) {
                throw std::runtime_error("Failed to initialize robotsLock");
            }
    }

    // Constructor with map provided to set the map alongside default constructor information
    SimulationDriver::SimulationDriver(Map selectedMap) : selectedMap(selectedMap), mongo_wrapper(std::nullopt), start(std::chrono::system_clock::now()) {
            if (pthread_rwlock_init(&robotsLock, nullptr) != 0) {
                throw std::runtime_error("Failed to initialize robotsLock");
            }
    }

    // Add the given robot to the simulation
    void SimulationDriver::addRobot(Robot& robot)
    {
        pthread_rwlock_wrlock(&robotsLock);
        int id = robot.getId();
        while (usedIds.find(id) != usedIds.end()) {
            id++;
        }
        // Update the robot's ID to the unique value
        robot.setId(id);
        // Mark the ID as used and add the robot to the fleet
        usedIds.insert(usedIds.end(), id);
        robots.push_back(std::move(robot));
        if (mongo_wrapper) mongo_wrapper->get().upsertRobotData(robot.toJson());
        pthread_rwlock_unlock(&robotsLock);
    }

    // Converts a given string to one of the robot type
    RobotType SimulationDriver::stringToRobotType(std::string type) {
        if (type == "Vacuum") {
            return RobotType::Vacuum;
        } else if (type == "Shampoo") {
            return RobotType::Shampoo;
        } else {
            return RobotType::Scrubber;
        }
    }

    // Remove robot from the simulation using the id provided
    Robot& SimulationDriver::removeRobot(int id){
        pthread_rwlock_wrlock(&robotsLock);
        int index = 0;
        for(Robot& r : robots){
            if(r.getId() == id){
                robots.erase(robots.begin() + index);
                if (mongo_wrapper) mongo_wrapper->get().moveRobotToRemoved(id);
                pthread_rwlock_unlock(&robotsLock);
                return r;
            }
            else index++;
        }
        pthread_rwlock_unlock(&robotsLock);
        return DEFAULT_ROBOT; // Return the default robot if not found
    }

    // Clear the list of robots
    void SimulationDriver::clear(){
        pthread_rwlock_wrlock(&robotsLock);
        robots.clear();
        pthread_rwlock_unlock(&robotsLock);
    }

    // Assign the robot an available index
    int SimulationDriver::assignRobotIndex(){
        while (usedIds.find(robot_index) != usedIds.end()) {
            robot_index++;
        }
        usedIds.insert(robot_index);
        return robot_index;
    }

    // Return the specified robot with the requested id (purely for testing purposes)
    Robot* SimulationDriver::getRobot(int id) {
        pthread_rwlock_rdlock(&robotsLock);
        for(int i = 0; i < robots.size(); i++){
            if(robots[i].getId()==id){
                pthread_rwlock_unlock(&robotsLock);
                return &robots[i];
            }
        }
        pthread_rwlock_unlock(&robotsLock);
        return nullptr;
    }


    // Gets robot WITHOUT a read lock, only for use if called inside update_all
    Robot* SimulationDriver::internal_getRobot(int id) {
        for(int i = 0; i < robots.size(); i++){
            if(robots[i].getId()==id){
                return &robots[i];
            }
        }
        return nullptr;
    }

    // Converts all robots to JSON and puts all information in a vector to return
    std::vector<nlohmann::json> SimulationDriver::getFleet() {
        pthread_rwlock_rdlock(&robotsLock);
        std::vector<nlohmann::json> info;
        for (Robot robo : robots) {
            info.push_back(robo.toJson());
        }
        pthread_rwlock_unlock(&robotsLock);
        return info;
    };

    // Updates all robots by calling update on them, updating the mongodb, and returning the messages
    // to be displayed to user after clearing the internal "queue" of messages
    std::vector<nlohmann::json> SimulationDriver::update_all(){
        std::cout << "update all called \n";
        pthread_rwlock_wrlock(&robotsLock);
        if (resetFlag){
            bool noCleaners = true;
            for (Robot& r : robots) {noCleaners = noCleaners & (r.getStatus() != Status::Active);}
            if (noCleaners){
                selectedMap.resetRoomCleanliness();
                alreadyAssigned.clear();
                messages.insert(messages.end(), nlohmann::json{{"Type", "Rooms Reset"},{"Message", "All Rooms Cleanliness have been reset"}});
                resetFlag = false;
            }
        }

        for(Robot& r : robots){
            update(r);
            std::cout << "updating: " << r.toString() << "\n";
        }
        pthread_rwlock_unlock(&robotsLock);
        if (mongo_wrapper){
            pthread_rwlock_rdlock(&robotsLock);
            nlohmann::json robots = getFleet();
                for (nlohmann::json robo : robots) {
                    mongo_wrapper->get().upsertRobotData(robo);
                }
            pthread_rwlock_unlock(&robotsLock);
        }
        std::vector<nlohmann::json> messsages_copy = messages;
        messages.clear();
        return messsages_copy;
    }

    // Given a robot, moves it forward one time tick in logic for cleaning based on its status, tasks, and other states
    void SimulationDriver::update(Robot& r){
        if(r.getStatus() == Status::Inactive)
        {
            // std::cout << r.getId() << " has status inactive" << "\n";
            if(r.getQueue().size() != 0)
            {
                r.incrementTasksAttempted();
                r.move(r.getQueue().front());
                // std::cout << r.getId() << " has post-move location: " << r.getLocation() << "\n";

                r.setStatus(Status::Active);
            }
            else if(r.getBatteryLevel() < 60){
                if(r.getBatteryLevel() == 59)
                    r.setBatteryLevel(60);
                else
                    r.chargeRobot();
            }
        }
        else if(r.getStatus() == Status::Active)
        {
            if(std::stoi(selectedMap.getRoomCleanliness(std::to_string(r.getLocation()))) >= 10)
            {
                messages.insert(messages.end(), nlohmann::json{{"Type", "Clean Complete"},{"Message", "Robot " + std::to_string(r.getId()) + " has finished cleaning " + selectedMap.getRoomName(std::to_string(r.getLocation()))}});
                r.incrementTasksCompleted();
                if(r.getQueue().size() != 0)
                {
                    r.popQueue();
                    if(r.getQueue().size() == 0){
                        r.setStatus(Status::Inactive);
                        r.move(-1);
                    }
                    else{
                        r.incrementTasksAttempted();
                        r.move(r.getQueue().front());
                    }
                }
                else {
                    r.setStatus(Status::Inactive);
                    r.move(-1);
                }
            }
            else{
                // std::cout << "clean about to be called; ";
                bool successfulClean = r.clean();
                if(!successfulClean){
                    r.decrementBatteryLevel(1);
                    r.setStatus(Status::Error);
                    std::queue<int> tempQueue = r.getQueue();
                    std::vector<int> reassignment = {};
                    std::cout << "To be potentially reassigned: ";
                    while (!tempQueue.empty()) {
                        reassignment.push_back(tempQueue.front());
                        std::cout << tempQueue.front() << ", ";
                        tempQueue.pop();
                    }
                    // std::cout << "\n";
                    std::vector<int> reassigned = re_assignmentModule(reassignment);
                    // std::cout << "Actually reassigned: ";
                    if(reassigned.size() > 0){
                        for(int r : reassigned){
                            tempQueue.push(r);
                            // std::cout << r << ", ";
                        }
                    }
                    // std::cout << "\n" << "HERE ";
                    r.setQueue(tempQueue);
                    // r.clearQueue();
                    int choice = rand() % 2;
                    // std::cout << "HERE3 ";

                    switch(choice){     // SEND ERROR TO MONGODB
                        case 1:
                            reportSimError(r.reportError(), "Cannot clean room due to Robot Damage");
                            return;
                        default:
                            reportSimError(r.reportError(), "Cannot clean room due to Sensor Error");
                            return;
                    }
                    r.move(-1);
                }
                else{
                    int current_cleanliness = std::stoi(selectedMap.getRoomCleanliness(std::to_string(r.getLocation())));
                    current_cleanliness++;
                    selectedMap.updateRoomCleanliness(std::to_string(r.getLocation()), std::to_string(current_cleanliness));
                    
                    if (r.getBatteryLevel() <= 0){
                        reportSimError(r.reportError(), "Robot Battery Died");
                    }
                }
                r.decrementBatteryLevel(1);
                
            }
        }
        else if(r.getStatus() == Status::BeingFixed)
        {
            if(r.getPauseTicks() > 0) {
                r.decrementPauseTicks();
            }
            else {
                r.setStatus(Status::Inactive);
                messages.insert(messages.end(), nlohmann::json{{"Type", "Clean Complete"},{"Message", "Robot " + std::to_string(r.getId()) + " has been fixed!"}});
            }
        }
        // pthread_rwlock_unlock(&robotsLock); 
    }

// Method to start fixing of a given robot by setting its pauseticks
int SimulationDriver::fixRobot(int id){
        pthread_rwlock_wrlock(&robotsLock);
        for(Robot& r : robots){
            if(r.getId() == id){
                r.setStatus(Status::BeingFixed);
                r.setBatteryLevel(60);
                r.move(-1);
                r.setPauseTicks(10);
                pthread_rwlock_unlock(&robotsLock);
                return 0;
            }
        }
        pthread_rwlock_unlock(&robotsLock);
        return 0;
}           

// Reports a given error from simulation adding time data to it given robot error in JSON and the details
// of error as a string and also creates a message to be passed upwards to UI for the dialog box and error dashboard
void SimulationDriver::reportSimError(nlohmann::json robotErr, std::string errorNotes) {
    float time = (std::chrono::duration<float>(std::chrono::system_clock::now() - start)).count();
    robotErr["Time"] = std::to_string((int)time / 60) + " minutes and " + 
                    std::to_string((int)time % 60) + " seconds";
    robotErr["ErrorNotes"] = errorNotes;
    if (mongo_wrapper) mongo_wrapper->get().logError(robotErr);
    robotErr["Message"] = "Error has occured for robot " + 
                    std::to_string(std::stoi(robotErr["ID"].dump())) + " at location " + 
                    selectedMap.getRoomName(std::to_string(std::stoi(robotErr["Location"].dump())))
                    + " because " + errorNotes;
    robotErr["Type"] = "Error";
    messages.insert(messages.end(), robotErr);
}


// The assignment algorithm takes a list of tasks & assigns them to valid robots 
std::vector<int> SimulationDriver::assignmentModule(std::vector<int> tasks){
    pthread_rwlock_wrlock(&robotsLock);
    std::cout << "Size of incoming: " << tasks.size();
    std::vector<int> unAssignedTasks = {};
    std::set<int> taskSet = {};
    alreadyAssigned.insert(-1);
    for(int task : tasks){
        taskSet.insert(task);
    }
    for(int task : taskSet){
        if(alreadyAssigned.count(task) == 1) break;
        std::string task_string = std::to_string(task);
        int min_time = INT_MAX;
        int min_robot_id = -1;
        for(auto r : robots){
            std::vector<std::string> valid_floors = type_mappings[r.getType()];
            bool valid_type = false;
            for(auto f : valid_floors){
                if(selectedMap.getFloorType(task_string) == f) {
                    valid_type = true;
                    break;
                }
            }
            if(valid_type && r.getStatus() != Status::Error && r.getStatus() != Status::BeingFixed){   // TYPE MATCHES FLOOR TYPE & ROBOT WORKS
                if(r.timeRemaining() < min_time){
                    min_time = r.timeRemaining();
                    min_robot_id = r.getId();
                }
            }
        }
        // std::cout << "gave task " << task << " to robot " << this->getRobot(min_robot_id)->getId() << " with type " 
        if(min_robot_id == -1){
            unAssignedTasks.push_back(task);
            // std::cout << "IMPOSSIBLE TASK! " << "\n";
        }
        else{
            this->internal_getRobot(min_robot_id)->addTask(task);    //add task
            alreadyAssigned.insert(task);

        }
        // pthread_rwlock_unlock(&robotsLock);
    }
    std::cout << "size: " << unAssignedTasks.size() << "\n";
    pthread_rwlock_unlock(&robotsLock);
    return unAssignedTasks;
}

// Reassigns the tasks of a robot that has broken down
std::vector<int> SimulationDriver::re_assignmentModule(std::vector<int> tasks){
    std::cout << "Size of incoming: " << tasks.size() << "\n";
    std::vector<int> unAssignedTasks = {};
    std::set<int> taskSet = {};
    // alreadyAssigned.insert(-1);
    for(int task : tasks){
        taskSet.insert(task);
    }
    for(int task : taskSet){
        // if(alreadyAssigned.count(task) == 1) break;
        std::string task_string = std::to_string(task);
        int min_time = INT_MAX;
        int min_robot_id = -1;
        for(auto r : robots){
            std::vector<std::string> valid_floors = type_mappings[r.getType()];
            bool valid_type = false;
            for(auto f : valid_floors){
                if(selectedMap.getFloorType(task_string) == f) {
                    valid_type = true;
                    break;
                }
            }
            if(valid_type && r.getStatus() != Status::Error && r.getStatus() != Status::BeingFixed){   // TYPE MATCHES FLOOR TYPE & ROBOT WORKS
                if(r.timeRemaining() < min_time){
                    min_time = r.timeRemaining();
                    min_robot_id = r.getId();
                }
            }
        }
        // std::cout << "gave task " << task << " to robot " << this->getRobot(min_robot_id)->getId() << " with type " 
        // << this->getRobot(min_robot_id)->typeToString(this->getRobot(min_robot_id)->getType()) << "\n";
        // pthread_rwlock_wrlock(&robotsLock);
        if(min_robot_id == -1){
            std::cout << task << " not reassigned \n";
            unAssignedTasks.push_back(task);

        }
        else{
            this->internal_getRobot(min_robot_id)->addTask(task);    //add task
            std::cout << "Assigned: " << task << "to robot: " << min_robot_id << "\n";
            // alreadyAssigned.insert(task);

        }
        // pthread_rwlock_unlock(&robotsLock);
    }
    std::cout << "size of unassigned: " << unAssignedTasks.size() << "\n";
    return unAssignedTasks;
}


// Reset the rooms in the map to be clean
void SimulationDriver::resetRooms(){
    pthread_rwlock_rdlock(&robotsLock);
    resetFlag = true;
    pthread_rwlock_unlock(&robotsLock);
}

