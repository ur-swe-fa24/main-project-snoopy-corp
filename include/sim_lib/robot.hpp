#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <vector>
#include <string>
#include "map.hpp"

enum class RobotType{
    Shampoo, Scrubber, Vacuum
};

enum class Status{
    Active, Inactive, Error
};

class Robot{

    public: 
        Robot();
        Robot(RobotType type, int id);
        Robot(RobotType type, int id, Map currentMap);

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
        std::string getMapName();
        RobotType getType() { return type; }
        std::string getRoomStatus();
        static std::string robotTypeToString(RobotType type); 

        // Temporarily Public, will turn Private soon through update function
        bool clean();    //returns false if an error occurs when trying to clean this tick, pure virtual so makes Robot abstract
        void reportError();     //triggered when clean() returns false
        void move(int room_num);

    protected:
        int id;
        RobotType type;
        Status status = Status::Active;
        int location = 0;   // an index of where it is on the currently loaded map
        int tasks_completed; // lifetime counter 
        int tasks_attempted; // lifetime counter
        int progress_task;  // progresss through current task (out of 10)
        int progress_queue; // progress through current queue, can get length of the queue itself to see how much left
        std::vector<int> queue;
        int battery_level;
        Map currentMap;  
        
};

#endif