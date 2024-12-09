#ifndef SCRUBBER_ROBOT_HPP
#define SCRUBBER_ROBOT_HPP

#include "robot.hpp"

class ScrubberRobot : public Robot{

    public:  
        ScrubberRobot(int id);
        ScrubberRobot(int id, float failure_rate);
        nlohmann::json toJson() override;

    private:
        int WaterLevel;  // Water Level for the the scrubber robot      
};

#endif