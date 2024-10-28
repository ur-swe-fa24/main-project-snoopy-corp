#include "../../include/dashboard/dashboard.hpp"
#include "../../include/sim_lib/simulation_driver.hpp"
#include <iostream>

// The only constructor for the dashboard that gets a vector of robots and starts the dashboard
Dashboard::Dashboard(std::vector<Robot> robots) : robots(robots) {
    // When fully implemented, will move to run on separate thread
    std::string choice = "U";
    while(true) {
        if (choice == "U") {
            std::cout << "Here are the available robot with their statuses:" << std::endl;
            for (Robot robot : robots) {
                std::cout << "\nRobot ID " + std::to_string(robot.getId()) << std::endl;
                std::string type = "";
                std::string status;
                RobotType roboType = robot.getType();
                switch (roboType) {
                    case RobotType::Shampoo: 
                        type = "Shampoo";
                        break;
                    case RobotType::Scrubber: 
                        type = "Scrubber";
                        break;
                    default:
                        type = "Vacuum";
                }
                switch(robot.getStatus()) {
                    case Status::Active: 
                        status = "Active";
                        break;
                    case Status::Inactive: 
                        status = "Inactive";
                        break;
                    case Status::Error: 
                        status = "Error";
                }
                std::cout << "Robot is a " + type + " Robot with " + status + " status on Map " + robot.getMapName() + " at location " + std::to_string(robot.getLocation()) << std::endl;
                std::cout << "Robot has battery level of " + std::to_string(robot.getBatteryLevel()) << std::endl;
                // Things to occur
                // std::cout << "Robot has an efficiency of " + std::to_string(robot.getEfficiency()) << std::endl;
                // std::cout << "Robot's current task: " + std::to_string(robot.getProgressTask()) << std::endl;
                // std::cout << "Robot's queued task: " + std::to_string(robot.getProgressQueue()) << std::endl;
                // Robot type specific metric may have to use this unsafe typecasting to downcast if can't figure alternative:
                // VacuumRobot* shamp = static_cast<VacuumRobot*>(&robot);
            }
        }
        else if (choice == "F") {
            get_feedback();    
        }
        else {
            std::cout << "Exiting and Closing..." << std::endl;
            std::getline (std::cin,choice); // Clear the buffer before exiting
            break;
        }
        std::cout << "Input U to update status, F to give feedback, and E to exit: ";
        std::cin >> choice;
    }
}

// Constructor for one robot
Dashboard::Dashboard(Robot robot) {Dashboard({robot});}

// Default Constructor with no robot
Dashboard::Dashboard() {Dashboard(std::vector<Robot>{});}

// TODO at a later sprint
void Dashboard::create_chart(std::vector<Robot> robots, std::string data_name) const {
    // General Helper function to create chart for robot(s) for a particular data type
    return;
}

// Basic function to provide feedback and capture it with input output
std::string Dashboard::get_feedback() const {
    std::cout << "Thanks for giving us feedback! \nIf this is a concern, we will respond as soon as possible. Please type your feedback below and hit Enter." << std::endl;
    std::string feedback;
    while ((getchar()) != '\n');
    std::getline(std::cin,feedback);
    return feedback;
}