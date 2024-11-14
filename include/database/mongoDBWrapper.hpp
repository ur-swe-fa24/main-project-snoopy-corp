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
    MongoDBWrapper(const std::string& uri, const std::string& db_name, const std::string& active_collection_name, const std::string& removed_collection_name);
    // Insert or update a robot's data
    void upsertRobotData(bool isActive,
                         int id,
                         const std::optional<std::string>& type,
                         const std::string& status,
                         const std::optional<int>& location,
                         const std::optional<std::string>& mapName,
                         const std::optional<std::string>& roomStatus
    );
    // Remove a robot by moving it from active to removed collection
    void moveRobotToRemoved(int id);
                        

private:
    mongocxx::client client_;
    mongocxx::database db_;
    mongocxx::collection active_collection_;
    mongocxx::collection removed_collection_;
};

#endif // MONGODBWRAPPER_HPP
