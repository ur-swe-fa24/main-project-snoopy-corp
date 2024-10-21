#ifndef LIVE_ROBOT_DASH_HPP
#define LIVE_ROBOT_DASH_HPP

#include "include/sim_lib/robot.hpp"
#include "include/dashboard/dashboard.hpp"

class LiveRobotDash : public Dashboard {
    public:
        LiveRobotDash();
        LiveRobotDash(int robotId);
    private:
        Status status;
        // Map curr_map;
        int location;
        int progress_task;
        int progress_queue {robot_.getProgressQueue()};
        int queue_length {robot_.getQueue().size()};
};

#endif // LIVE_ROBOT_DASH_HPP