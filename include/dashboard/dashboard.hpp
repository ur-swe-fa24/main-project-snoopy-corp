#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <vector>
#include <string>
#include "../../include/sim_lib/robot.hpp"

class Dashboard {
    public:
        Dashboard();                    // Default constructor with no robots
        Dashboard(Robot robot);         // For a singular robot
        Dashboard(std::vector<Robot> robots);   // For multiple robots
        void create_chart(std::vector<Robot> robots, std::string data_name) const;
        std::string get_feedback() const;

    protected:
        std::vector<Robot> robots;
        // Unused and to be removed from framework upon discussion
        // int id;
        // RobotType type;
};

#endif // DASHBOARD_HPP