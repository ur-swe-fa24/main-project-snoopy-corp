#ifndef SIMULATION_DRIVER_HPP
#define SIMULATION_DRIVER_HPP

#include <vector>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <mutex>
#include <thread>
#include <optional>
#include "robot.hpp"
#include "map.hpp"
#include "../dashboard/dashboard.hpp"
#include <climits>
#include <magic_enum.hpp>

#include "../database/mongoDBWrapper.hpp"

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
        Robot* getRobot(int id);
        std::vector<nlohmann::json> getFleet();
        void update_all();
        void update(Robot& r);
        RobotType stringToRobotType(std::string type);
        int fixRobot(int id);
        int chargeRobot(int id);
        void assignmentModule(std::vector<int> tasks);
        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        void setMongoWrapper(MongoDBWrapper& wrapper) {mongo_wrapper = wrapper;}

    private:
        std::vector<Robot> robots;
        std::unordered_set<int> usedIds;   // Track all used robot IDs
        pthread_rwlock_t robotsLock;
        Map selectedMap;
        std::optional<std::reference_wrapper<MongoDBWrapper>> mongo_wrapper;
        int robot_index = 0;
        Robot DEFAULT_ROBOT;
        void constructRobot();
        std::unordered_map<RobotType, std::vector<std::string>> type_mappings = {
            {RobotType::Scrubber, {"Wood", "Tile"}},
            {RobotType::Vacuum, {"Wood", "Tile", "Carpet"}},
            {RobotType::Shampoo, {"Carpet"}}
        };
        void reportSimError(nlohmann::json robotErr, std::string errorNotes);
        
};


#endif