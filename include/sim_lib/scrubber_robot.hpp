#ifndef SCRUBBER_ROBOT_HPP
#define SCRUBBER_ROBOT_HPP

#include "robot.hpp"

class ScrubberRobot : public Robot{

    public:  
        ScrubberRobot(int id);
        ScrubberRobot(int id, float failure_rate);
        nlohmann::json toJson() override;
        bool decrementBatteryLevel(int amt) override;
        void loadRobot() override {WaterLevel = 15;}

        void setWaterLevel(int level) {WaterLevel = level;} // Setter for Water Level
        int getWaterLevel() {return WaterLevel;} // Getter for Water Level

    private:
        int WaterLevel;  // Water Level for the the scrubber robot      
};

#endif