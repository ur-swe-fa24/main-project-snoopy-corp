#ifndef SIMULATION_DRIVER_HPP
#define SIMULATION_DRIVER_HPP

#include <vector>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <mutex>
#include <thread>
#include "robot.hpp"
#include "map.hpp"
#include "../dashboard/dashboard.hpp"

class SimulationDriver{

    public:
        SimulationDriver();
        explicit SimulationDriver(Map selectedMap);
        void addRobot(Robot& robot);
        Robot& removeRobot(int id);
        void clear();
        void toString();
        int getRobotIndex() { return robot_index; }
        int assignRobotIndex();
        Map getSelectedMap() { return selectedMap; }
        void start_dashboard();
        Robot* getRobot(int id);
        std::vector<nlohmann::json> getFleet();
        void update_all();
        void update(Robot& r);
        RobotType stringToRobotType(std::string type);
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

    private:
        std::vector<Robot> robots;
        std::unordered_set<int> usedIds;   // Track all used robot IDs
        pthread_rwlock_t robotsLock;
        Map selectedMap;
        int robot_index = 0;
        Robot DEFAULT_ROBOT;
        void constructRobot();
        void reportSimError(nlohmann::json err);
        
};

#endif