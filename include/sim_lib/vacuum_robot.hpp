#ifndef VACUUM_ROBOT_HPP
#define VACUUM_ROBOT_HPP

#include <vector>
#include "robot.hpp"


class VacuumRobot : public Robot{

    public: 
        VacuumRobot();
        VacuumRobot(int id, Map currentMap);
        VacuumRobot(int id);

    private:
        int TrashbagLevel;
        bool clean();        
};

#endif