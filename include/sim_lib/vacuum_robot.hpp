#ifndef VACUUM_ROBOT_HPP
#define VACUUM_ROBOT_HPP

#include "robot.hpp"

class VacuumRobot : public Robot{

    public: 
        VacuumRobot(int id);
        VacuumRobot(int id, float failure_rate);

        nlohmann::json toJson() override;

    private:
        int TrashbagLevel; // Trash Bag Level for the the scrubber robot
};

#endif