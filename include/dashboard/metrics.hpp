#ifndef METRICS_HPP
#define METRICS_HPP

#include "include/dashboard/dashboard.hpp"

class MetricsDash : public Dashboard {
    public:
        MetricsDash();
        MetricsDash(int robotId);
    private:
        float efficiency;
        float error_rate;
        int runtime;
};

#endif // METRICS_HPP