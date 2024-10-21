#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <vector>
#include <string>
#include "include/sim_lib/robot.hpp"

class Dashboard {
    public:
        Dashboard();
        Dashboard(int robotId);
        void create_chart(std::vector<Robot> robots, std::string data_name) const;
        std::string get_feedback(std::string feedback) const;

    protected:
        Robot robot;
        int id;
        RobotType type;
};

#endif // DASHBOARD_HPP