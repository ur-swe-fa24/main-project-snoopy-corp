#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <vector>
#include <string>
#include <queue>
#include <nlohmann/json.hpp>
#include <magic_enum.hpp>
#include <random>
#include <iostream>

enum class RobotType{
    Shampoo, Scrubber, Vacuum
};

enum class Status{
    Active, Inactive, Error, Deleted, BeingFixed
};

class Robot{

    public: 
        Robot();
        // Robot(RobotType type, int id);
        Robot(RobotType type, int id);
        Robot(RobotType type, int id, float failure_rate);

        // Copy constructor
        // Robot(const Robot& other);

        // Move operator
        // Robot& operator=(Robot&& other);
        
        float getEfficiency();
        int getId() const;
        Status getStatus();
        int getLocation();
        int getProgressTask();
        int getProgressQueue();
        std::queue<int> getQueue();
        void addTask(int room);
        int getBatteryLevel();
        void incrementBatteryLevel(int amt);
        void setBatteryLevel(int amt) { battery_level = amt; }
        void update();  // calls the robot's internal logic to clean, reportError, etc. - basically a time update from the simulation driver
        static std::string typeToString(RobotType type);
        static std::string statusToString(Status status);  
        static std::string getRobotTypeFullName(char type);
        std::string toString();
        RobotType getType() { return type; }
        float getFailureRate() { return failure_rate; }
        // std::string getRoomStatus();
        virtual nlohmann::json toJson();
        // Temporarily Public, will turn Private soon through update function
        void move(int room_num);
        bool clean();    //returns false if an error occurs when trying to clean this tick, pure virtual so makes Robot abstract
        nlohmann::json reportError();
        float getRandom();
        float genFailRate();
        float getFailRate() { return failure_rate; }
        void popQueue();
        void setStatus(Status s);
        void setId(int newId);
        void setPauseTicks(int s) { pause_ticks = s; }
        void incrementPauseTicks() { pause_ticks -= 1; }
        int getPauseTicks() { return pause_ticks; }
        void chargeRobot() { battery_level += 2; }

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
        float failure_rate;
             //triggered when clean() returns false

        std::mt19937 gen;
        std::uniform_real_distribution<float> float_distribution;
        std::uniform_real_distribution<float> fail_distribution;

        int pause_ticks = 0;    // how long the robot should wait before taking action due to error fixing or charging
    

};

#endif