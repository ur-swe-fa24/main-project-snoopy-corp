#ifndef SIMULATION_DRIVER_HPP
#define SIMULATION_DRIVER_HPP

#include <vector>
#include "robot.hpp"

class SimulationDriver{

    public:
        SimulationDriver();
        explicit SimulationDriver(std::vector<Robot> robots);
        void addRobot(Robot robot);
        Robot removeRobot(int id);
        void clear();
        void toString();
    private:
        std::vector<Robot> robots;
        
};

#endif