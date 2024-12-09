#ifndef SHAMPOO_ROBOT_HPP
#define SHAMPOO_ROBOT_HPP

#include "robot.hpp"

class ShampooRobot : public Robot{

    public: 
        ShampooRobot(int id);
        ShampooRobot(int id, float failure_rate);
        nlohmann::json toJson() override;
        bool decrementBatteryLevel(int amt) override;
        void loadRobot() override {ShampooLevel = 15;}

        void setShampooLevel(int level) {ShampooLevel = level;} // Setter for Shmapoo Level
        int getShampooLevel() {return ShampooLevel;} // Getter for Shampoo Level

    private:
        int ShampooLevel; // Shampoo Level for the the scrubber robot

};

#endif