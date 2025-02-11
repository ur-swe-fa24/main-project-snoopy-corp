#include <iostream>
#include <string>
#include <thread>
#include <stdexcept>

#include "sim_lib/robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/vacuum_robot.hpp"
#include "sim_lib/simulation_driver.hpp"
#include "dashboard/dashboard.hpp"
#include "sim_lib/map.hpp"
#include "database/mongoDBWrapper.hpp"  // Include the MongoDBWrapper
#include "wxwidgets_lib/wxwidgets.hpp"

int main() {
    mongocxx::instance instance{};  // Initialize MongoDB instance for the entire application

    // Initialize MongoDB wrapper to log robot actions
    MongoDBWrapper mongo_wrapper("mongodb://localhost:27017", "robot_db", "robot_data", "removed_robots", "error_log");

    // Set up initial map and simulation driver
    nlohmann::json roomsEx1 = {
        {"1", {{"Room", "Kitchen"}, {"Cleaning Status", "Unclean"}, {"FloorType", "Wood"}}},
        {"2", {{"Room", "Office"}, {"Cleaning Status", "Clean"}, {"FloorType", "Carpet"}}},
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "Unclean"}, {"FloorType", "Tile"}}}
    };
    Map m("map1", roomsEx1);
    SimulationDriver s(m);

    // Thread to go each second and call the clean method
    // Each 3 'seconds', call the update method on each robot and update the database
    std::atomic<bool> simulationThread = true;
    std::thread update_stuff {[&s, &mongo_wrapper, &simulationThread](){
        while (simulationThread){
            s.update_all();
            nlohmann::json robots = s.getFleet();
            for (nlohmann::json robo : robots) {
                mongo_wrapper.upsertRobotData(robo);
            }
            std::this_thread::sleep_for (std::chrono::seconds(2));
        }}};
    std::this_thread::sleep_for (std::chrono::seconds(5));
    simulationThread = false;
    update_stuff.join();

    // std::thread dash{
    //     [](){wxIMPLEMENT_APP(MyWidget);}
    // }
    // WxWIDGETS MUST BE ON MAIN THREAD AND OTHERS IN THE ONINIT OF SIMULATION DRIVER


    // std::string input;
    // std::cout << "Enter a command (A - Add, R - Remove, V - View, M - Move, C - Clean, E - Exit): ";
    // while (true) {
    //     std::getline(std::cin, input);

    //     // Convert input to uppercase to handle case insensitivity
    //     input = std::toupper(input[0]);

    //     if (input == "E") {
            // End simulation, join the threads, and finish
    //         std::cout << "Exiting the program. Goodbye!\n";
            // simulationThread = false;
            // update_stuff.join();
    //         break;
    //     }

    //     else if (input == "A") {
    //         std::cout << "Enter Robot Type (S for Scrubber, H for Shampoo, V for Vacuum): ";
    //         std::getline(std::cin, input);
    //         input = std::toupper(input[0]);

    //         Robot* robot = nullptr;
    //         int robotIndex = s.assignRobotIndex();  // Assign a unique robot index
    //         std::string robotTypeName = Robot::getRobotTypeFullName(input[0]);
    //         Map map = s.getSelectedMap();
    //         if (robotTypeName == "Scrubber") {
    //             robot = new ScrubberRobot(robotIndex, map);
    //         } else if (robotTypeName == "Shampoo") {
    //             robot = new ShampooRobot(robotIndex, map);
    //         } else if (robotTypeName == "Vacuum") {
    //             robot = new VacuumRobot(robotIndex, map);
    //         } else {
    //             std::cout << "Invalid robot type. Please enter S, H, or V.\n";
    //             continue;
    //         }

        //     s.addRobot(*robot);  // Add robot to the simulation driver
        //     mongo_wrapper.upsertRobotData(robot->toJson());
        //     std::cout << "Robot added successfully with ID " << robot->getId() << ".\n";
        //     delete robot;  // Clean up dynamically allocated robot after adding it to the vector
        // }

    //     else if (input == "R") {
    //         std::cout << "Enter ID of Robot to be removed: ";
    //         std::getline(std::cin, input);
    //         // int id = std::stoi(input);

    //         // try {
    //         //     Robot removedRobot = s.removeRobot(id);  // Remove robot from simulation
    //         //     mongo_wrapper.insertRobotData(removedRobot.toJson());
    //         //     std::cout << "Robot with ID " << id << " removed successfully.\n";
    //         // } catch (const std::exception& e) {
    //         //     std::cout << "Error: " << e.what() << ". Please check the ID and try again.\n";
    //         // }
    //     }

    //     else if (input == "V") {
    //         std::cout << "Displaying all robots:\n";
    //         s.start_dashboard();
    //     }

    //     else if (input == "M") {
    //         std::cout << "Enter ID of Robot to be moved: ";
    //         std::getline(std::cin, input);
    //         int id = std::stoi(input);

    //         std::cout << "Enter room number Robot should move to: ";
    //         std::getline(std::cin, input);
    //         int newLocation = std::stoi(input);

    //         Robot* robot = s.getRobot(id);
    //         if (robot) {
    //             robot->move(newLocation);
    //             mongo_wrapper.upsertRobotData(robot->toJson());
    //             std::cout << "Robot with ID " << id << " moved to room " << newLocation << ".\n";
    //         } else {
    //             std::cout << "Robot with ID " << id << " not found. Please check the ID and try again.\n";
    //         }
    //     }

    //     else if (input == "C") {
    //         std::cout << "Enter ID of Robot to clean: ";
    //         std::getline(std::cin, input);
    //         int id = std::stoi(input);

    //         Robot* robot = s.getRobot(id);
    //         if (robot) {
    //             if (robot->getLocation() == 0) {
    //                 std::cout << "Robot needs to be moved to a location first in order to clean.\n";
    //             } else {
    //                 bool success = robot->clean();
    //                 mongo_wrapper.upsertRobotData(robot->toJson());
    //                 std::cout << "Robot with ID " << id << (success ? " successfully cleaned the room.\n" : " encountered an error while cleaning.\n");
    //             }
    //         } else {
    //             std::cout << "Robot with ID " << id << " not found. Please check the ID and try again.\n";
    //         }
    //     }

    //     else {
    //         std::cout << "Invalid input. Enter a command (A - Add, R - Remove, V - View, M - Move, C - Clean, E - Exit): ";
    //     }

    //     std::cout << "\n";  // Add some space for readability
    // }

    return 0;
}