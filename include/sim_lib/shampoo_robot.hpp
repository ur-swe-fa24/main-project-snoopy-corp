#ifndef SHAMPOO_ROBOT_HPP
#define SHAMPOO_ROBOT_HPP

#include <vector>
#include "robot.hpp"


class ShampooRobot : public Robot{

    public: 
        ShampooRobot();
        ShampooRobot(int id);
        ShampooRobot(int id, Map currentMap);
        nlohmann::json toJson() override;

    private:
        int ShampooLevel;
        bool clean();

};

#endif