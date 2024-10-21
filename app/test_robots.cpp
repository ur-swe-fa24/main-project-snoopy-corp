#include <iostream>
#include <string>

#include "sim_lib/robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/vacuum_robot.hpp"

int main(){
    // std::cout << "compiles!";
    ScrubberRobot scrub(0, 0);
    ShampooRobot shampoo(1,0);
    VacuumRobot vacuum(2,0);

    scrub.toString();
    shampoo.toString();
    vacuum.toString();

    // std::cout << "scrub: " << scrub.toString() << ", shampoo: " << shampoo.toString() << ", vacuum: " << vacuum.toString();
    return 0;
}