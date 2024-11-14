#include "../../include/sim_lib/simulation_driver.hpp"
#include <thread>

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
        std::lock_guard<std::mutex> guard(robotsMutex);
        robots.push_back(robot);
    }

    // Needed = operator
    Robot SimulationDriver::removeRobot(int id){
        std::lock_guard<std::mutex> guard(robotsMutex);
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
        std::lock_guard<std::mutex> guard(robotsMutex);
        for (Robot r : robots){
            r.toString();
        }
    }

    int SimulationDriver::assignRobotIndex(){
        robot_index++;
        return robot_index-1;
    }

    void SimulationDriver::start_dashboard(){
        std::thread dash {[this](){auto dash = Dashboard(robots);}};
        // TODO: Once dashboard is on a separate screen, this thread can be detached instead
        // TODO: After mongoDB integration, also switch dashboard to using mongoDB pulls to avoid race conditions
        dash.join();
    }

    Robot* SimulationDriver::getRobot(int id) {
        std::lock_guard<std::mutex> guard(robotsMutex);
        for(int i = 0; i < robots.size(); i++){
            if(robots[i].getId()==id){
                return &robots[i];
            }
        }
        return nullptr;
    }