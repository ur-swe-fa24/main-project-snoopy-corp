#ifndef LIVE_ROBOT_DASH_HPP
#define LIVE_ROBOT_DASH_HPP

#include "include/dashboard/dashboard.hpp"
#include "include/map.hpp"

class LiveRobotDash : public Dashboard {
    public:
        LiveRobotDash();
        LiveRobotDash(int robotId);
    private:
        Status status;
        Map curr_map;
        int location;
        int progress_task;
        int progress_queue;
        int queue_length;
};

#endif // LIVE_ROBOT_DASH_HPP