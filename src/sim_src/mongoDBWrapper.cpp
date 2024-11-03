#include "../../include/sim_lib/mongoDBWrapper.hpp"

MongoDBWrapper::MongoDBWrapper(const std::string& uri, const std::string& db_name, const std::string& collection_name)
    : client_(mongocxx::uri{uri}), db_(client_[db_name]), collection_(db_[collection_name]) {

    // Configure spdlog pattern and log level
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    spdlog::set_level(spdlog::level::info);

    spdlog::info("MongoDB Wrapper initialized.");
    spdlog::info("Connected to MongoDB at {}", uri);
}

void MongoDBWrapper::insertRobotData(int id, const std::string& type, const std::string& status,
                                     int location, const std::string& map, const std::string& currentRoomStatus) {
    auto doc = make_document(
        kvp("ID", id),
        kvp("Type", type),
        kvp("Status", status),
        kvp("Location", location),
        kvp("Map", map),
        kvp("Current Room Status", currentRoomStatus)
    );

    try {
        auto result = collection_.insert_one(doc.view());
        if (result) {
            spdlog::info("Inserted robot data with ID: {}", result->inserted_id().get_oid().value.to_string());
        } else {
            spdlog::error("Failed to insert robot data.");
        }
    } catch (const mongocxx::exception& e) {
        spdlog::error("MongoDB insertion error: {}", e.what());
    }
}
