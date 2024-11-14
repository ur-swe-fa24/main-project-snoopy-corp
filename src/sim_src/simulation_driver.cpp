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
        robots.push_back(robot);
    }

    // Needed = operator
    Robot SimulationDriver::removeRobot(int id){
        int index = 0;
        for(Robot r : robots){
            if(r.getId() == id){
                robots.erase(robots.begin() + index);
                return r;
            }
            else index++;
        }
        return DEFAULT_ROBOT;
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
        robot_index++;
        return robot_index-1;
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