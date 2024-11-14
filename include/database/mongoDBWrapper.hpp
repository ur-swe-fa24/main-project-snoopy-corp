#ifndef MONGODBWRAPPER_HPP
#define MONGODBWRAPPER_HPP

#include "spdlog/spdlog.h"
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>
#include <string>


using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

class MongoDBWrapper {
public:
    MongoDBWrapper(const std::string& uri, const std::string& db_name, const std::string& collection_name);
    void upsertRobotData(
        int id, 
        std::optional<std::string> type,           // Optional: Robot type (e.g., "Scrubber", "Vacuum")
        std::optional<std::string> status,         // Optional: Status (e.g., "Active", "Removed")
        std::optional<int> location,               // Optional: Current location of the robot
        std::optional<std::string> map,            // Optional: Map name where the robot is located
        std::optional<std::string> currentRoomStatus // Optional: Status of the room the robot is in
    );

                        

private:
    mongocxx::client client_;
    mongocxx::database db_;
    mongocxx::collection collection_;
};

#endif // MONGODBWRAPPER_HPP
