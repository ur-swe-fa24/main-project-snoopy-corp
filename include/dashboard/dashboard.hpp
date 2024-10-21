#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <vector>
#include <string>
// #include "include/robot/robot.hpp"

class Dashboard {
    public:
        // void create_chart(vector<Robot> robots, RobData data_name) const;
        std::string get_feedback(std::string feedback) const;

    private:
        int id_;
        // Robot robot_;
        // Type type_;
        long time_;
}

#endif // DASHBOARD_HPP