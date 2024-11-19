#include "../../include/sim_lib/_sim_lib.hpp"
#include <iostream>
    // Default constructor 
    SimulationDriver::SimulationDriver(){}
        
    SimulationDriver::SimulationDriver(Map selectedMap) : selectedMap(selectedMap) {}



    void SimulationDriver::addRobot(Robot& robot)
    {
        int id = robot.getId();
        if (usedIds.find(id) != usedIds.end()) {
            id++;
        }
        // Update the robot's ID to the unique value
        robot.setId(id);
        // Mark the ID as used and add the robot to the fleet
        usedIds.insert(id);
        robots.push_back(std::move(robot));
    }

    // Needed = operator
    Robot& SimulationDriver::removeRobot(int id){
        int index = 0;
        for(Robot& r : robots){
            if(r.getId() == id){
                robots.erase(robots.begin() + index);
                return r;
            }
            else index++;

//     Robot SimulationDriver::removeRobot(int id){
//         auto it = std::find_if(robots.begin(), robots.end(),
//         [id](const Robot& r) { return r.getId() == id; });

//         if (it != robots.end()) {
//             Robot removedRobot = std::move(*it); // Create a copy of the robot being removed
//             robots.erase(it);                   // Erase the robot from the vector
//             return removedRobot;
        }

        return DEFAULT_ROBOT; // Return the default robot if not found
    }

    void SimulationDriver::constructRobot(){
        return;
    }

    void SimulationDriver::clear(){
        robots.clear();
    }

    void SimulationDriver::toString(){
        for (Robot& r : robots){
            r.toString();
        }
    }

    int SimulationDriver::assignRobotIndex(){
        while (usedIds.find(robot_index) != usedIds.end()) {
            robot_index++;
        }
        usedIds.insert(robot_index);
        return robot_index++;
    }

    // void SimulationDriver::start_dashboard(){
    //     auto dash = Dashboard(robots);
    // }

    Robot* SimulationDriver::getRobot(int id) {
        for(int i = 0; i < robots.size(); i++){
            if(robots[i].getId()==id){
                return &robots[i];
            }
        }
        return nullptr;
    }

    std::vector<nlohmann::json> SimulationDriver::getFleet() {
        std::vector<nlohmann::json> info;
        // for (Robot robo : robots) {
        //     info.push_back(robo.toJson());
        // }
        return info;
    };

    void SimulationDriver::update_all(){
        for(Robot& r : robots){
            // std::cout << r.getId() << "\n";
            update(r);
        }
    }

    void SimulationDriver::update(Robot& r){
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
        //else: error case
    }