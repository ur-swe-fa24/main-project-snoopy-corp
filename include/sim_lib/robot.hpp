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
        static std::string typeToString(RobotType type);
        static std::string statusToString(Status status);  
        static std::string getRobotTypeFullName(char type);
        std::string toString();
        virtual nlohmann::json toJson();
        void move(int room_num);
        bool clean();
        nlohmann::json reportError();
        float getRandom();
        float genFailRate();
        void popQueue();
        void setStatus(Status s);
        void setId(int newId);
        void incrementTasksAttempted() { tasks_attempted += 1; } // Increment Tasks Attempted by 1
        void incrementTasksCompleted() { tasks_completed += 1; } // Increment Tasks Completed by 1
        int getTA() { return tasks_attempted; } // Getter for Tasks Attempted
        int getTC() { return tasks_completed; } // Getter for Tasks Completed
        RobotType getType() { return type; } // Getter for the type of the robot
        float getFailureRate() { return failure_rate; } // Getter for the failure rate
        float getFailRate() { return failure_rate; } // Getter for the failure rate
        void setBatteryLevel(int amt) { battery_level = amt; } // Sets the battery level to given amount
        void setQueue(std::queue<int> q) { queue = q; } // Sets the queue of tasks
        void setPauseTicks(int s) { pause_ticks = s; } // Setter for Pause Ticks
        void decrementPauseTicks() { pause_ticks -= 1; } // Decrements Pause Ticks by 1
        int getPauseTicks() { return pause_ticks; } // Getter for Pause Ticks
        void chargeRobot() { battery_level += 2; } // Increase Battery Level by 2
        int timeRemaining() { return queue.size()*10; } // Return time remaining from queue size
    protected:
        int id; // Id of the robot where each id of active robot is unique
        RobotType type; // Type of the Robot determining floor types it can work
        Status status = Status::Inactive; // Status of the Robot
        int location = 0;   // an index of where it is on the currently loaded map
        int tasks_completed = 0; // lifetime counter 
        int tasks_attempted = 0; // lifetime counter
        int progress_task = 0;  // progresss through current task (out of 10)
        int progress_queue = 0; // progress through current queue, can get length of the queue itself to see how much left
        std::queue<int> queue; // Queue of tasks
        int battery_level; // Battery level of robot
        float failure_rate; //Trigger for robot clean returning false and having clean error

        std::mt19937 gen; // Random Number Generation
        std::uniform_real_distribution<float> float_distribution; // Distribution to return a random number
        std::uniform_real_distribution<float> fail_distribution; // Distribution to determine failure rate

        int pause_ticks = 0;    // how long the robot should wait before taking action due to error fixing or charging
    

};

#endif