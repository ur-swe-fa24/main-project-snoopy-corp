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
#include <climits>
#include <magic_enum.hpp>


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
        int fixRobot(int id);
        int chargeRobot(int id);
        std::vector<int> assignmentModule(std::vector<int> tasks);

    private:
        std::vector<Robot> robots;
        std::unordered_set<int> usedIds;   // Track all used robot IDs
        pthread_rwlock_t robotsLock;
        Map selectedMap;
        int robot_index = 0;
        Robot DEFAULT_ROBOT;
        void constructRobot();
        std::unordered_map<RobotType, std::vector<std::string>> type_mappings = {
            {RobotType::Scrubber, {"Wood", "Tile"}},
            {RobotType::Vacuum, {"Wood", "Tile", "Carpet"}},
            {RobotType::Shampoo, {"Carpet"}}
        };
};


#endif