#include "../../include/sim_lib/simulation_driver.hpp"
#include <thread>

    // Overloaded constructor with type and id parameters
    SimulationDriver::SimulationDriver() {}
    SimulationDriver::SimulationDriver(std::vector<Robot> robots) : robots(robots){}
    SimulationDriver::SimulationDriver(Map selectedMap) : selectedMap(selectedMap){}
    SimulationDriver::SimulationDriver(std::vector<Robot> robots, Map selectedMap) : robots(robots), selectedMap(selectedMap){}

    void SimulationDriver::addRobot(Robot robot)
    {
        robots.push_back(robot);
    }
    
    Robot SimulationDriver::removeRobot(int id){
        int index = 0;
        Robot removedRobot;
        bool found = false;
        for (Robot r : robots) {
            if(r.getId()==id)
            {
                removedRobot = r;
                robots.erase(robots.begin() + index);
                break;
            }
            else index++;
        }   
        if(found) return removedRobot;
        else return Robot(RobotType::Scrubber, -1);
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
        std::thread dash {[this](){auto dash = Dashboard(robots);}};
        // TODO: Once dashboard is on a separate screen, this thread can be detached instead
        // TODO: After mongoDB integration, also switch dashboard to using mongoDB pulls to avoid race conditions
        dash.join();
    }

    Robot* SimulationDriver::getRobot(int id) {
        for(int i = 0; i < robots.size(); i++){
            if(robots[i].getId()==id){
                return &robots[i];
            }
        }
        return nullptr;
    }