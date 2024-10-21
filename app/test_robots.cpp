#include <iostream>
#include <string>

#include "sim_lib/robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/vacuum_robot.hpp"
#include "sim_lib/simulation_driver.hpp"

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

    SimulationDriver s;
    std::string input;
    int id_index;
    while (true) {
        std::cout << "Add, Remove, or Exit: " << "\n";
        std::getline(std::cin, input); 

        if (input == "Exit") break; 
        else if(input == "Add"){
            std::cout << "Enter Type" << "\n";
            std::getline(std::cin, input); 
            if(input == "Scrubber") s.addRobot(ScrubberRobot(id_index, 0));
            else if(input == "Shampoo") s.addRobot(ShampooRobot(id_index, 0));
            else s.addRobot(VacuumRobot(id_index, 0));
            id_index++;
        }
        else if(input == "Remove"){
            std::cout << "Enter ID of Robot to be removed" << "\n";
            std::getline(std::cin, input); 
            s.removeRobot(stoi(input));
        }
        else
            std::cout << "Invalid input, try again";

        std::cout << "All current robots: " << "\n";
        s.toString();
    }

    return 0;
}