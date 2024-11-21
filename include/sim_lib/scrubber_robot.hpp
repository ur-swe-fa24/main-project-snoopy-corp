#ifndef SCRUBBER_ROBOT_HPP
#define SCRUBBER_ROBOT_HPP

#include <vector>
#include "robot.hpp"
#include <string>

class ScrubberRobot : public Robot{

    public:  
        // ScrubberRobot();
        // ScrubberRobot(int id);
        ScrubberRobot(int id);
        ScrubberRobot(int id, float failure_rate);
        nlohmann::json toJson() override;

    private:
        int WaterLevel;
        bool clean();
        
};

#endif