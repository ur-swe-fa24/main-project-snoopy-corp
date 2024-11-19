#include "../../include/sim_lib/_sim_lib.hpp"
#include <pthread.h>
#include <iostream>
#include <magic_enum.hpp>
#include <algorithm>
#include <iostream>
    // Default constructor 
    SimulationDriver::SimulationDriver(){
        if (pthread_rwlock_init(&robotsLock, nullptr) != 0) {
                throw std::runtime_error("Failed to initialize robotsLock");
            }
    }
        
    SimulationDriver::SimulationDriver(Map selectedMap) : selectedMap(selectedMap) {
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

    // Needed = operator
    Robot& SimulationDriver::removeRobot(int id){
        pthread_rwlock_wrlock(&robotsLock);
        int index = 0;
        for(Robot& r : robots){
            if(r.getId() == id){
                robots.erase(robots.begin() + index);
                pthread_rwlock_unlock(&robotsLock);
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
        pthread_rwlock_unlock(&robotsLock);
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

    // void SimulationDriver::start_dashboard(){
    //     std::thread dash {[this](){auto dash = Dashboard(robots);}};
    //     dash.join();
    // }

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
        return info;
        pthread_rwlock_unlock(&robotsLock);
    };

    void SimulationDriver::update_all(){
        pthread_rwlock_rdlock(&robotsLock);
        for(Robot& r : robots){
            // std::cout << r.getId() << "\n";
            update(r);
        }
        pthread_rwlock_unlock(&robotsLock);
    }

    void SimulationDriver::update(Robot& r){
        pthread_rwlock_rdlock(&robotsLock);
        // std::cout << r.getId() << "\n";
        if(r.getStatus() == Status::Inactive)
        {
            // std::cout << r.getId() << " has status inactive" << "\n";
            if(r.getQueue().size() != 0)
            {
                // std::cout << r.getId() << " has " << r.getQueue().front() << " in queue" << "\n";
                // std::cout << r.getId() << " has pre-move location: " << r.getLocation() << "\n";
                r.move(r.getQueue().front());
                // std::cout << r.getId() << " has post-move location: " << r.getLocation() << "\n";

                r.setStatus(Status::Active);
            }
            // std::cout << "N";
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
                if(!successfulClean) r.reportError();
                else{
                    int current_cleanliness = std::stoi(selectedMap.getRoomCleanliness(std::to_string(r.getLocation())));
                    current_cleanliness++;
                    selectedMap.updateRoomCleanliness(std::to_string(r.getLocation()), std::to_string(current_cleanliness));
                    r.setBatteryLevel(-1);
                }
                
            }
        }
        pthread_rwlock_unlock(&robotsLock);
        //else: error case
    }