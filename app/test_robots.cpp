#include <iostream>
#include <string>

#include "sim_lib/robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/vacuum_robot.hpp"
#include "sim_lib/simulation_driver.hpp"
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
        {"1" , {"kitchen", "1", "wood"}},
        {"2", {"office", "5", "carpet"}},
        {"3" , {"bathroom", "7", "tile"}}
    };
    Map m("map1", roomsEx1);
    SimulationDriver s(m);

    std::string input;
    while (true) {
        std::cout << "Add, Remove, Move, Clean, or Exit: " << "\n";
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
        else if(input == "Move"){
            /// TO BE
        }
        else if(input == "Clean"){
            /// TO BE
        }
        else
            std::cout << "Invalid input, try again";

        std::cout << "All current robots: " << "\n";
        s.toString();
    }

    return 0;
}