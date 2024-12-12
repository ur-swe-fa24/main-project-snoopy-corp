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
#include "../database/mongoDBWrapper.hpp"
#include <climits>
#include <magic_enum.hpp>
#include <set>

class SimulationDriver{

    public:
        SimulationDriver();
        explicit SimulationDriver(Map selectedMap);
        void addRobot(Robot& robot);
        Robot& removeRobot(int id);
        void clear();
        int getRobotIndex() { return robot_index; }
        int assignRobotIndex();
        Map getSelectedMap() { return selectedMap; }
        Robot* getRobot(int id);
        Robot* internal_getRobot(int id);
        std::vector<nlohmann::json> getFleet();
        std::vector<nlohmann::json> update_all();
        void update(Robot& r);
        RobotType stringToRobotType(std::string type);
        int fixRobot(int id);
        int chargeRobot(int id);
        std::vector<int> assignmentModule(std::vector<int> tasks);
        std::vector<int> re_assignmentModule(std::vector<int> tasks);
        void setMongoWrapper(MongoDBWrapper& wrapper) {mongo_wrapper = wrapper;}


    private:
        std::vector<Robot> robots; // Vector of all robots
        std::unordered_set<int> usedIds;   // Track all used robot IDs
        pthread_rwlock_t robotsLock; // Thread locks for accessing and editing robots vector and robots in it
        Map selectedMap; // Store the selected map in the simulation
        std::optional<std::reference_wrapper<MongoDBWrapper>> mongo_wrapper; // Pointer for the mongo wrapper that's initially null
        int robot_index = 0; // Largest robot index for available indices
        Robot DEFAULT_ROBOT; // A default robot for testing
        void reportSimError(nlohmann::json robotErr, std::string errorNotes);
        std::set<int> alreadyAssigned; // Set of tasks that are already assigned
        std::unordered_map<RobotType, std::vector<std::string>> type_mappings = {
            {RobotType::Scrubber, {"Wood", "Tile"}},
            {RobotType::Vacuum, {"Wood", "Tile", "Carpet"}},
            {RobotType::Shampoo, {"Carpet"}}
        }; // Vector of robot type to room type
        std::chrono::system_clock::time_point start; // Start time of the simulation set during constructor
        std::vector<nlohmann::json> messages; // Messages to send to UI to pass to the user
};


#endif