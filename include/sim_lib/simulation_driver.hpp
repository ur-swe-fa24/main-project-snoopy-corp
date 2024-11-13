#ifndef SIMULATION_DRIVER_HPP
#define SIMULATION_DRIVER_HPP

#include <vector>
#include <nlohmann/json.hpp>
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
        std::vector<nlohmann::json> getFleet();
    private:
        std::vector<Robot> robots;
        Map selectedMap;
        int robot_index = 0;
        
};

#endif