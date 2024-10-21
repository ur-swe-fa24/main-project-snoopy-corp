#ifndef SCRUBBER_ROBOT_HPP
#define SCRUBBER_ROBOT_HPP

#include <vector>
#include "robot.hpp"


class ScrubberRobot : public Robot{

    public:  
        ScrubberRobot();
        ScrubberRobot(int id, int currentMap);

    private:
        int WaterLevel;
        bool clean() override;
        
};

#endif