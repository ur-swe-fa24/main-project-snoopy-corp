#include "../../include/sim_lib/simulation_driver.hpp"



    // Default constructor 
    SimulationDriver::SimulationDriver() : DEFAULT_MAP(Map("DEFAULT_MAP", {
        {"-1", {{"Room", "DEFAULT"}, {"Cleaning Status", "-1"}, {"FloorType", "DEFAULT"}}}})), 
        DEFAULT_ROBOT(Robot(RobotType::Vacuum, -1, DEFAULT_MAP)), robots({DEFAULT_ROBOT}) {

        }
        
    SimulationDriver::SimulationDriver(Map selectedMap) : selectedMap(selectedMap),
        DEFAULT_ROBOT(Robot(RobotType::Vacuum, -1, selectedMap)), robots({DEFAULT_ROBOT}) {
        }



    void SimulationDriver::addRobot(Robot robot)
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
    Robot SimulationDriver::removeRobot(int id){
        auto it = std::find_if(robots.begin(), robots.end(),
        [id](const Robot& r) { return r.getId() == id; });

        if (it != robots.end()) {
            Robot removedRobot = std::move(*it); // Create a copy of the robot being removed
            robots.erase(it);                   // Erase the robot from the vector
            return removedRobot;
        }

        return DEFAULT_ROBOT; // Return the default robot if not found
    }

    void SimulationDriver::constructRobot(){
        json def = {
        {"-1", {{"Room", "DEFAULT"}, {"Cleaning Status", "-1"}, {"FloorType", "DEFAULT"}}}
        };
        Map DEFAULT_MAP = Map("DEFAULT_MAP", def);
        Robot DEFAULT_ROBOT = Robot(RobotType::Vacuum, 0, DEFAULT_MAP);
        std::vector<Robot> robots = {DEFAULT_ROBOT};
    }

    void SimulationDriver::clear(){
        robots.clear();
    }

    void SimulationDriver::toString(){
        for (Robot r : robots){
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

    void SimulationDriver::start_dashboard(){
        auto dash = Dashboard(robots);
    }

    Robot* SimulationDriver::getRobot(int id) {
        for(int i = 0; i < robots.size(); i++){
            if(robots[i].getId()==id){
                return &robots[i];
            }
        }
        return nullptr;
    }