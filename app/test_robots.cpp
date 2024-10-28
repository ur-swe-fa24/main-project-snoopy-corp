#include <iostream>
#include <string>

#include "sim_lib/robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/vacuum_robot.hpp"
#include "sim_lib/simulation_driver.hpp"
#include "dashboard/dashboard.hpp"
#include "sim_lib/map.hpp"

int main(){
    // std::cout << "compiles!";
    // ScrubberRobot scrub(0, 0);
    // ShampooRobot shampoo(1,0);
    // VacuumRobot vacuum(2,0);
    // std::vector<Robot> list;
    // list.push_back(scrub);
    // list.push_back(shampoo);
    // list.push_back(vacuum);

    // scrub.toString();
    // shampoo.toString();
    // vacuum.toString();

 

    std::map<std::string, std::vector<std::string>> roomsEx1 = {
        {"0" , {"default", "default", "defaultA"}},
        {"1" , {"kitchen", "Unclean", "wood"}},
        {"2", {"office", "Unclean", "carpet"}},
        {"3" , {"bathroom", "Unclean", "tile"}}
    };
    Map m("map1", roomsEx1);
    SimulationDriver s(m);

    std::string input;
    while (true) {
        std::cout << "Add, Remove, View, Move, Clean, or Exit: " << "\n";
        std::getline(std::cin, input); 

        if (input == "Exit") break; 
        else if(input == "Add"){
            std::cout << "Enter Type" << "\n";
            std::getline(std::cin, input); 
            if(input == "Scrubber") s.addRobot(ScrubberRobot(s.assignRobotIndex(), s.getSelectedMap()));
            else if(input == "Shampoo") s.addRobot(ShampooRobot(s.assignRobotIndex(), s.getSelectedMap()));
            else s.addRobot(VacuumRobot(s.assignRobotIndex(), s.getSelectedMap()));
        }
        else if(input == "Remove"){
            std::cout << "Enter ID of Robot to be removed" << "\n";
            std::getline(std::cin, input); 
            s.removeRobot(stoi(input));
        }
        else if(input == "View"){
            std::cout << "Starting the dashboard" << "\n";
            s.start_dashboard();
        }
        else if(input == "Move"){
            std::cout << "Enter ID of Robot to be moved" << "\n";
            std::getline(std::cin, input); 
            
            int id = stoi(input);

            std::cout << "Enter room number Robot should move to" << "\n";
            std::getline(std::cin, input); 
            
            Robot* robot = s.getRobot(id);
            robot->move(stoi(input));
            // std::cout << robot->toString() << std::endl;
        }
        else if(input == "Clean"){
            std::cout << "Enter ID of Robot to clean" << "\n";
            std::getline(std::cin, input); 
            Robot* robot = s.getRobot(stoi(input));

            if (robot->getLocation() == 0) {
                std::cout << "Robot needs to be moved to a location first in order to clean" << std::endl;
            } else {
            robot->clean();
            //std::cout << robot.toString() << std::endl;
            }
        }
        else
            std::cout << "Invalid input, try again";

        std::cout << "All current robots: " << "\n";
        s.toString();
    }

    return 0;
}