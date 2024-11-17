#include "../../include/database/mongoDBWrapper.hpp"
#include <iostream>


// Constructor
MongoDBWrapper::MongoDBWrapper(const std::string& uri, const std::string& db_name, const std::string& active_collection_name, const std::string& removed_collection_name)
    :client_(mongocxx::uri{uri}), 
     db_(client_[db_name]), 
     active_collection_(db_[active_collection_name]),
     removed_collection_(db_[removed_collection_name]) {

    // Configure spdlog pattern and log level
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
    spdlog::set_level(spdlog::level::info);

    spdlog::info("MongoDB Wrapper initialized.");
    spdlog::info("Connected to MongoDB at {}", uri);
}

// Insert or update a robot's data
void MongoDBWrapper::upsertRobotData(bool isActive,
                                     int id,
                                     const std::optional<std::string>& type,
                                     const std::string& status,
                                     const std::optional<int>& location,
                                     const std::optional<std::string>& mapName,
                                     const std::optional<std::string>& roomStatus) {

    auto& collection = isActive ? active_collection_ : removed_collection_;

    try {
        // Build the filter to find the robot by ID
        bsoncxx::builder::basic::document filterBuilder;
        filterBuilder.append(bsoncxx::builder::basic::kvp("ID", id));

        // Build the update document
        bsoncxx::builder::basic::document updateBuilder;
        updateBuilder.append(
            bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document subDoc) {
                subDoc.append(bsoncxx::builder::basic::kvp("Status", status));

                if (type) {
                    subDoc.append(bsoncxx::builder::basic::kvp("Type", *type));
                }

                if (location) {
                    subDoc.append(bsoncxx::builder::basic::kvp("Location", *location));
                }

                if (mapName) {
                    subDoc.append(bsoncxx::builder::basic::kvp("Map", *mapName));
                }

                if (roomStatus) {
                    subDoc.append(bsoncxx::builder::basic::kvp("Room Status", *roomStatus));
                }
            })
        );

        // Perform the upsert operation
        collection.update_one(filterBuilder.view(), updateBuilder.view(), mongocxx::options::update().upsert(true));

        spdlog::info("Upserted robot with ID {} successfully.", id);
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
            // Insert the robot into the removed collection
            removed_collection_.insert_one(robot->view());

            // Remove the robot from the active collection
            active_collection_.delete_one(filterBuilder.view());

            spdlog::info("Moved robot with ID {} from active to removed collection.", id);
        } else {
            spdlog::warn("Robot with ID {} not found in active collection.", id);
        }
    } catch (const mongocxx::exception& e) {
        spdlog::error("Error moving robot to removed collection: {}", e.what());
    }
}