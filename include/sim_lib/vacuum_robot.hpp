#ifndef VACUUM_ROBOT_HPP
#define VACUUM_ROBOT_HPP

#include "robot.hpp"

class VacuumRobot : public Robot{

    public: 
        VacuumRobot(int id);
        VacuumRobot(int id, float failure_rate);
        nlohmann::json toJson() override;
        bool decrementBatteryLevel(int amt) override;
        void loadRobot() override {TrashbagLevel = 0;}

        void setTrashBagLevel(int level) {TrashbagLevel = level;} // Setter for Trash Bag Level
        int getTrashBagLevel() {return TrashbagLevel;} // Getter for Trash Bag Level

    private:
        int TrashbagLevel; // Trash Bag Level for the the scrubber robot
};

#endif