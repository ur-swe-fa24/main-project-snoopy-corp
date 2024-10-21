#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <vector>
#include <string>
#include "include/sim_lib/robot.hpp"

class Dashboard {
    public:
        Dashboard();                    // For the metrics of the whole fleet (or default to first robot and message to create robot if no robots)
        Dashboard(Robot robot);         // For a singular robot
        void create_chart(std::vector<Robot> robots, std::string data_name) const;
        std::string get_feedback() const;

    protected:
        Robot robot;
        int id;
        RobotType type;
};

#endif // DASHBOARD_HPP