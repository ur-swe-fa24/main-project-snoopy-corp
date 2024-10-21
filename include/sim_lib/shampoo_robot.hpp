#ifndef SHAMPOO_ROBOT_HPP
#define SHAMPOO_ROBOT_HPP

#include <vector>
#include "robot.hpp"


class ShampooRobot : public Robot{

    public: 
        ShampooRobot();
        ShampooRobot(int id, int currentMap);

    private:
        int ShampooLevel;
        bool clean() override;

};

#endif