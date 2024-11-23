#include "../../include/sim_lib/simulation_driver.hpp"
#include <ostream>
#include <pthread.h>
#include <iostream>
#include <magic_enum.hpp>
#include <algorithm>
#include <iostream>
#include <random>
#include <cstdlib>



    // Default constructor 
    SimulationDriver::SimulationDriver() : mongo_wrapper(nullptr){
        if (pthread_rwlock_init(&robotsLock, nullptr) != 0) {
                throw std::runtime_error("Failed to initialize robotsLock");
            }
    }

    SimulationDriver::SimulationDriver(Map selectedMap) : selectedMap(selectedMap), mongo_wrapper(nullptr) {
            if (pthread_rwlock_init(&robotsLock, nullptr) != 0) {
                throw std::runtime_error("Failed to initialize robotsLock");
            }
    }

    void SimulationDriver::addRobot(Robot& robot)
    {
        pthread_rwlock_wrlock(&robotsLock);
        int id = robot.getId();
        if (usedIds.find(id) != usedIds.end()) {
            id++;
        }
        // Update the robot's ID to the unique value
        robot.setId(id);
        // Mark the ID as used and add the robot to the fleet
        usedIds.insert(id);
        robots.push_back(std::move(robot));
        pthread_rwlock_unlock(&robotsLock);
    }

    RobotType SimulationDriver::stringToRobotType(std::string type) {
        if (type == "Vacuum") {
            return RobotType::Vacuum;
        } else if (type == "Shampoo") {
            return RobotType::Shampoo;
        } else {
            return RobotType::Scrubber;
        }
    }



    // Needed = operator
    Robot& SimulationDriver::removeRobot(int id){
        // pthread_rwlock_wrlock(&robotsLock);
        int index = 0;
        for(Robot& r : robots){
            if(r.getId() == id){
                robots.erase(robots.begin() + index);
                // pthread_rwlock_unlock(&robotsLock);
                return r;
            }
            else index++;

//     Robot SimulationDriver::removeRobot(int id){
//         auto it = std::find_if(robots.begin(), robots.end(),
//         [id](const Robot& r) { return r.getId() == id; });

//         if (it != robots.end()) {
//             Robot removedRobot = std::move(*it); // Create a copy of the robot being removed
//             robots.erase(it);                   // Erase the robot from the vector
//             pthread_rwlock_unlock(&robotsLock);
//             return removedRobot;
        }
        // pthread_rwlock_unlock(&robotsLock);
        return DEFAULT_ROBOT; // Return the default robot if not found
    }

    void SimulationDriver::constructRobot(){
        return;
    }

    void SimulationDriver::clear(){
        pthread_rwlock_wrlock(&robotsLock);
        robots.clear();
        pthread_rwlock_unlock(&robotsLock);
    }

    void SimulationDriver::toString(){
        pthread_rwlock_rdlock(&robotsLock);
        for (Robot& r : robots){
            r.toString();
        }
        pthread_rwlock_unlock(&robotsLock);
    }

    int SimulationDriver::assignRobotIndex(){
        while (usedIds.find(robot_index) != usedIds.end()) {
            robot_index++;
        }
        usedIds.insert(robot_index);
        return robot_index++;
    }

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

    std::vector<nlohmann::json> SimulationDriver::getFleet() {
        pthread_rwlock_rdlock(&robotsLock);
        std::vector<nlohmann::json> info;
        for (Robot robo : robots) {
            info.push_back(robo.toJson());
        }
        pthread_rwlock_unlock(&robotsLock);
        return info;
    };

    void SimulationDriver::update_all(){
        pthread_rwlock_wrlock(&robotsLock);
        for(Robot& r : robots){
            update(r);
        }
        pthread_rwlock_unlock(&robotsLock);
    }

    void SimulationDriver::update(Robot& r){
        if(r.getBatteryLevel() <= 0){
            r.reportError("Battery has died :(");
        }
        else if(r.getStatus() == Status::Inactive)
        {
            // std::cout << r.getId() << " has status inactive" << "\n";
            if(r.getQueue().size() != 0)
            {
                r.move(r.getQueue().front());
                // std::cout << r.getId() << " has post-move location: " << r.getLocation() << "\n";

                r.setStatus(Status::Active);
            }
            else r.chargeRobot();
        }
        else if(r.getStatus() == Status::Active)
        {
            if(std::stoi(selectedMap.getRoomCleanliness(std::to_string(r.getLocation()))) >= 10)
            {
                if(r.getQueue().size() != 0)
                {
                    r.popQueue();
                    if(r.getQueue().size() == 0)
                        r.setStatus(Status::Inactive);
                    else
                        r.move(r.getQueue().front());
                }
                else r.setStatus(Status::Inactive);
            }
            else{
                // std::cout << "clean about to be called; ";
                bool successfulClean = r.clean();
                if(!successfulClean){
                    int choice = rand() % 2;
                    switch(choice){     // SEND ERROR TO MONGODB
                        case 1:
                            reportSimError(r.reportError("Cannot clean room due to Robot Damage"));
                            return;
                        default:
                            reportSimError(r.reportError("Cannot clean room due to Sensor Error"));
                            return;
                    }
                }
                else{
                    int current_cleanliness = std::stoi(selectedMap.getRoomCleanliness(std::to_string(r.getLocation())));
                    current_cleanliness++;
                    selectedMap.updateRoomCleanliness(std::to_string(r.getLocation()), std::to_string(current_cleanliness));
                    
                    if (r.getBatteryLevel() == 0){
                        reportSimError(r.reportError("Robot Battery Died"));
                    }
                }
                r.incrementBatteryLevel(1);
                
            }
        }
        else if(r.getStatus() == Status::BeingFixed)
        {
            if(r.getPauseTicks() > 0) r.incrementPauseTicks();
            else r.setStatus(Status::Inactive);
        }
        //else: error case
    }

int SimulationDriver::fixRobot(int id){
        pthread_rwlock_wrlock(&robotsLock);
        for(Robot& r : robots){
            if(r.getId() == id){
                // pthread_rwlock_unlock(&robotsLock);
                r.setStatus(Status::BeingFixed);
                r.setBatteryLevel(60);
                r.setPauseTicks(50);
            }
        }
        pthread_rwlock_unlock(&robotsLock);
        return 0;
}           

    void SimulationDriver::reportSimError(nlohmann::json err){
        float time = (std::chrono::system_clock::now() - start).count()/1000;
        err["Time"] = std::to_string((int)time / 60) + " minutes and" + 
                      std::to_string((int)time % 60) + " seconds";
        // REPORT ERROR IN THE MONGODB
    }