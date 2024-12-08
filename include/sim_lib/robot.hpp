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
        Robot(RobotType type, int id);
        Robot(RobotType type, int id, float failure_rate);
        
        float getEfficiency();
        void incrementTasksAttempted() { tasks_attempted += 1; }
        void incrementTasksCompleted() { tasks_completed += 1; }
        int getTA() { return tasks_attempted; }
        int getTC() { return tasks_completed; }
        int getId() const;
        Status getStatus();
        int getLocation();
        int getProgressTask();
        int getProgressQueue();
        std::queue<int> getQueue();
        void clearQueue();
        void addTask(int room);
        void addTask(std::vector<int> rooms);
        int getBatteryLevel();
        void decrementBatteryLevel(int amt);
        void setBatteryLevel(int amt) { battery_level = amt; }
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
        void setQueue(std::queue<int> q) { queue = q; }
        void setStatus(Status s);
        void setId(int newId);
        void setPauseTicks(int s) { pause_ticks = s; }
        void decrementPauseTicks() { pause_ticks -= 1; }
        int getPauseTicks() { return pause_ticks; }
        void chargeRobot() { battery_level += 2; }
        int timeRemaining() { return queue.size()*10; }
    protected:
        int id;
        RobotType type;
        Status status = Status::Inactive;
        int location = 0;   // an index of where it is on the currently loaded map
        int tasks_completed = 0; // lifetime counter 
        int tasks_attempted = 0; // lifetime counter
        int progress_task = 0;  // progresss through current task (out of 10)
        int progress_queue = 0; // progress through current queue, can get length of the queue itself to see how much left
        std::queue<int> queue; // Queue of tasks
        int battery_level; // Battery level of robot
        float failure_rate; //Trigger for robot clean returning false and having clean error

        std::mt19937 gen;
        std::uniform_real_distribution<float> float_distribution;
        std::uniform_real_distribution<float> fail_distribution;

        int pause_ticks = 0;    // how long the robot should wait before taking action due to error fixing or charging
    

};

#endif