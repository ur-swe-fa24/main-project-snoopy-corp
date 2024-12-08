#ifndef VACUUM_ROBOT_HPP
#define VACUUM_ROBOT_HPP

#include <vector>
#include "robot.hpp"


class VacuumRobot : public Robot{

    public: 
        // VacuumRobot();
        // VacuumRobot(int id);
        VacuumRobot(int id);
        VacuumRobot(int id, float failure_rate);

        nlohmann::json toJson() override;

    private:
        int TrashbagLevel;
};

#endif