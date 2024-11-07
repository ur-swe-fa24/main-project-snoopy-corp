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
    void insertRobotData(int id, const std::string& type, const std::string& status,
                         int location, const std::string& map, const std::string& currentRoomStatus);

private:
    mongocxx::client client_;
    mongocxx::database db_;
    mongocxx::collection collection_;
};

#endif // MONGODBWRAPPER_HPP
