#include "../../include/sim_lib/simulation_driver.hpp"



    // Overloaded constructor with type and id parameters
    SimulationDriver::SimulationDriver() {}
    SimulationDriver::SimulationDriver(std::vector<Robot> robots) : robots(robots){}
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
        else return Robot(RobotType::Scrubber, -1, 0);
    }

    void SimulationDriver::clear(){
        robots.clear();
    }

    void SimulationDriver::toString(){
        for (Robot r : robots){
            r.toString();
        }
    }