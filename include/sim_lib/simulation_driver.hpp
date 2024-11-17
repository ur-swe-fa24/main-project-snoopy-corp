#ifndef SIMULATION_DRIVER_HPP
#define SIMULATION_DRIVER_HPP

#include <vector>
#include <unordered_set>
#include "robot.hpp"
#include "map.hpp"
#include "../dashboard/dashboard.hpp"

class SimulationDriver{

    public:
        SimulationDriver();
        explicit SimulationDriver(std::vector<Robot> robots);
        explicit SimulationDriver(Map selectedMap);
        explicit SimulationDriver(std::vector<Robot> robots, Map selectedMap);
        void addRobot(Robot robot);
        Robot removeRobot(int id);
        void clear();
        void toString();
        int getRobotIndex() { return robot_index; }
        int assignRobotIndex();
        Map getSelectedMap() { return selectedMap; }
        void start_dashboard();
        Robot* getRobot(int id);
        std::vector<Robot> getFleet();
    private:
        std::vector<Robot> robots;
        std::unordered_set<int> usedIds;   // Track all used robot IDs
        Map selectedMap;
        int robot_index = 0;
        Robot DEFAULT_ROBOT;
        Map DEFAULT_MAP;
        void constructRobot();
        
};

#endif