#ifndef SHAMPOO_ROBOT_HPP
#define SHAMPOO_ROBOT_HPP

#include "robot.hpp"

class ShampooRobot : public Robot{

    public: 
        ShampooRobot(int id);
        ShampooRobot(int id, float failure_rate);
        nlohmann::json toJson() override;

    private:
        int ShampooLevel; // Shampoo Level for the the scrubber robot

};

#endif