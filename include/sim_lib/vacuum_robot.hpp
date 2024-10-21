#ifndef VACUUM_ROBOT_HPP
#define VACUUM_ROBOT_HPP

#include <vector>
#include "robot.hpp"


class VacuumRobot : public Robot{

    public: 
        VacuumRobot();
        VacuumRobot(int id, int currentMap);

    private:
        int TrashbagLevel;
        bool clean();        
};

#endif