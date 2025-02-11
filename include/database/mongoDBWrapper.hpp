#ifndef MONGODBWRAPPER_HPP
#define MONGODBWRAPPER_HPP

#include "spdlog/spdlog.h"
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>
#include <nlohmann/json.hpp>
#include <string>


using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;
using json = nlohmann::json;

class MongoDBWrapper {
public:
    MongoDBWrapper(
            const std::string& uri, 
            const std::string& db_name, 
            const std::string& active_collection_name, 
            const std::string& removed_collection_name,
            const std::string& error_collection_name
    );
    // Insert or update a robot's data
    void upsertRobotData(nlohmann::json robotData);
    // Remove a robot by moving it from active to removed collection
    void moveRobotToRemoved(int id);
    // Add Error log
    void logError(nlohmann::json robotData);
    // Retrieve data from Mongodb as json
    nlohmann::json getAllDataAsJson(const std::string& collectionType);
                        

private:
    // MongoDB client and database
    mongocxx::client client_;
    mongocxx::database db_;
    // MongoDB collections
    mongocxx::collection active_collection_;
    mongocxx::collection removed_collection_;
    mongocxx::collection error_collection_;
};

#endif // MONGODBWRAPPER_HPP
