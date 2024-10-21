#ifndef ERROR_LOG_HPP
#define ERROR_LOG_HPP

#include "include/dashboard/dashboard.hpp"

class ErrorLog : public Dashboard {
    public:
        ErrorLog();
        ErrorLog(Robot robot);
    private:
        std::string description;
        int timpestamp;
};

#endif // ERROR_LOG_HPP