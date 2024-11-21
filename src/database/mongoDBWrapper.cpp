#include "../../include/database/mongoDBWrapper.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>


// Constructor
MongoDBWrapper::MongoDBWrapper(
    const std::string& uri, 
    const std::string& db_name, 
    const std::string& active_collection_name, 
    const std::string& removed_collection_name,
    const std::string& error_collection_name):
        client_(mongocxx::uri{uri}), 
        db_(client_[db_name]), 
        active_collection_(db_[active_collection_name]),
        removed_collection_(db_[removed_collection_name]),
        error_collection_(db_[error_collection_name]) {

        // Configure spdlog pattern and log level
        spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
        spdlog::set_level(spdlog::level::info);

        spdlog::info("MongoDB Wrapper initialized.");
        spdlog::info("Connected to MongoDB at {}", uri);
}

// Insert or update a robot's data
void MongoDBWrapper::upsertRobotData(nlohmann::json robotData) {
    bool isActive = robotData["Status"] != "Deleted";
    auto& collection = isActive ? active_collection_ : removed_collection_;
    try {
        // Build the filter to find the robot by ID
        bsoncxx::builder::basic::document filterBuilder;
        filterBuilder.append(bsoncxx::builder::basic::kvp("ID", robotData["ID"].get<int>()));

        // Build the update document
        bsoncxx::builder::basic::document updateBuilder;
        updateBuilder.append(bsoncxx::builder::basic::kvp("$set", bsoncxx::from_json(robotData.dump())));

        // Perform the upsert operation
        collection.update_one(filterBuilder.view(), updateBuilder.view(), mongocxx::options::update().upsert(true));

        spdlog::info("Upserted robot with ID {} successfully.", std::to_string(robotData["ID"].get<int>()));
    } 
    catch (const mongocxx::exception& e) {
        spdlog::error("Error during upsert: {}", e.what());
    }
}

// Move a robot from active collection to removed collection
void MongoDBWrapper::moveRobotToRemoved(int id) {
    try {
        // Find the robot in the active collection
        bsoncxx::builder::basic::document filterBuilder;
        filterBuilder.append(bsoncxx::builder::basic::kvp("ID", id));

        auto robot = active_collection_.find_one(filterBuilder.view());
        if (robot) {
            // Modify the status to "Removed"
            nlohmann::json robotData = nlohmann::json::parse(bsoncxx::to_json(robot->view()));
            robotData["Status"] = "Removed";

            // Upsert to the removed collection
            upsertRobotData(robotData);

            // Remove from the active collection
            active_collection_.delete_one(filterBuilder.view());
            spdlog::info("Moved robot with ID {} from active to removed collection.", id);
        } else {
            spdlog::warn("Robot with ID {} not found in active collection.", id);
        }
    } catch (const mongocxx::exception& e) {
        spdlog::error("Error moving robot to removed collection: {}", e.what());
    }
}
// Add error log entry
void MongoDBWrapper::logError(nlohmann::json errorData) {
    try {
        // Validate the required fields in the input JSON
        if (!errorData.contains("Time") || !errorData.contains("ID") || 
            !errorData.contains("Location") || !errorData.contains("ErrorNotes")) {
            spdlog::error("ErrorData JSON missing required fields.");
            return;
        }

        // Build the log entry with required fields
        nlohmann::json logEntry = {
            {"Time", errorData["Time"]},
            {"ID", errorData["ID"]},
            {"Location", errorData["Location"]},
            {"ErrorNotes", errorData["ErrorNotes"]}
        };

        // Convert JSON to BSON
        auto bsonDoc = bsoncxx::from_json(logEntry.dump());

        // Insert into the error log collection
        error_collection_.insert_one(bsonDoc.view());

        spdlog::info("Logged error: {}", logEntry.dump());
    } 
    catch (const mongocxx::exception& e) {
        spdlog::error("Error logging robot error: {}", e.what());
    } 
    catch (const std::exception& e) {
        spdlog::error("JSON processing error: {}", e.what());
    }
}
