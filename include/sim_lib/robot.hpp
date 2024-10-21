#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <vector>
#include <string>

enum class RobotType{
    Shampoo, Scrubber, Vacuum
};

enum class Status{
    Active, Inactive, Error
};

class Robot{

    public: 
        Robot();
        Robot(RobotType type, int id, int currentMap);

        float getEfficiency();
        int getId();
        Status getStatus();
        int getLocation();
        int getProgressTask();
        int getProgressQueue();
        std::vector<int> getQueue();
        int getBatteryLevel();
        void update();  // calls the robot's internal logic to clean, reportError, etc. - basically a time update from the simulation driver
        std::string toString();

    protected:
        int id;
        RobotType type;
        Status status = Status::Active;
        int location;   // an index of where it is on the currently loaded map
        int tasks_completed; // lifetime counter 
        int tasks_attempted; // lifetime counter
        int progress_task;  // progresss through current task (out of 10)
        int progress_queue; // progress through current queue, can get length of the queue itself to see how much left
        std::vector<int> queue;
        int battery_level;
        int currentMap;  //being implemented by Adelina - int is just a placeholder

        bool clean();    //returns false if an error occurs when trying to clean this tick, pure virtual so makes Robot abstract
        void reportError();     //triggered when clean() returns false
        void move(int room_num);
        
};

#endif