#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <vector>
#include <string>
#include <queue>
#include "map.hpp"
#include <random>

enum class RobotType{
    Shampoo, Scrubber, Vacuum
};

enum class Status{
    Active, Inactive, Error
};

class Robot{

    public: 
        // Robot();
        // Robot(RobotType type, int id);
        Robot(RobotType type, int id, Map& currentMap);
        Robot(RobotType type, int id, Map& currentMap, float failure_rate);

        // Copy constructor
        Robot(const Robot& other);

        // Move operator
        Robot& operator=(Robot&& other);
        
        float getEfficiency();
        int getId() const;
        Status getStatus();
        int getLocation();
        int getProgressTask();
        int getProgressQueue();
        std::queue<int> getQueue();
        void addTask(int room);
        int getBatteryLevel();
        void update();  // calls the robot's internal logic to clean, reportError, etc. - basically a time update from the simulation driver
        std::string toString();
        std::string getMapName();
        RobotType getType() { return type; }
        float getFailureRate() { return failure_rate; }
        std::string getRoomStatus();
        static std::string robotTypeToString(RobotType type); 
        static std::string getRobotTypeFullName(char type);
        Map& getMap();
        // Temporarily Public, will turn Private soon through update function
        bool move(int room_num);
        virtual bool clean();    //returns false if an error occurs when trying to clean this tick, pure virtual so makes Robot abstract
        void reportError();
        float getRandom();
        float genFailRate();
        float getFailRate() { return failure_rate; }
        void setId(int newId);
        

    protected:
        int id;
        RobotType type;
        Status status = Status::Active;
        int location = 0;   // an index of where it is on the currently loaded map
        int tasks_completed; // lifetime counter 
        int tasks_attempted; // lifetime counter
        int progress_task;  // progresss through current task (out of 10)
        int progress_queue; // progress through current queue, can get length of the queue itself to see how much left
        std::queue<int> queue;
        int battery_level;
        Map& currentMap;  
        float failure_rate;
             //triggered when clean() returns false
        void setStatus(Status s);

        std::mt19937 gen;
        std::uniform_real_distribution<float> float_distribution;
        std::uniform_real_distribution<float> fail_distribution;

    

};

#endif