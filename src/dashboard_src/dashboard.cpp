#include "include/dashboard/dashboard.hpp"
#include <iostream>

Dashboard::Dashboard(Robot robot) : robot(robot), id(robot.getId()), type(robot.getType()) {}

void Dashboard::create_chart(std::vector<Robot> robots, std::string data_name) const {
    // General Helper function to create chart for robot(s) for a particular data type
    return;
}

std::string Dashboard::get_feedback() const {
    std::cout << "Thanks for giving us feedback!\n If this is a concern, we will respond as soon as possible. Please type your feedback below and hit Enter." << std::endl;
    std::string feedback = "";
    std::cin >> feedback;
    return feedback;
}