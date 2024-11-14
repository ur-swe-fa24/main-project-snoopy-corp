#include "../../include/database/mongoDBWrapper.hpp"


MongoDBWrapper::MongoDBWrapper(
    const std::string& uri, 
    const std::string& db_name, 
    const std::string& collection_name): 
        client_(mongocxx::uri{uri}), 
        db_(client_[db_name]), 
        collection_(db_[collection_name]) {

        // Configure spdlog pattern and log level
        spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");
        spdlog::set_level(spdlog::level::info);

        spdlog::info("MongoDB Wrapper initialized.");
        spdlog::info("Connected to MongoDB at {}", uri);
    }

// Update all fields or insert a new document if no match is founded

#include <optional>  // For using std::optional

void MongoDBWrapper::upsertRobotData(
    int id, 
    std::optional<std::string> type = std::nullopt,
    std::optional<std::string> status = std::nullopt,
    std::optional<int> location = std::nullopt,
    std::optional<std::string> map = std::nullopt,
    std::optional<std::string> currentRoomStatus = std::nullopt) {

    // Filter document to find robot by ID
    auto filter = make_document(kvp("ID", id));

    // Create an update document with only the fields that are provided
    auto update_doc_builder = bsoncxx::builder::basic::document{};

    update_doc_builder.append(bsoncxx::builder::basic::kvp("$set", [&](bsoncxx::builder::basic::sub_document subdoc) {
        // Always include the ID field in the filter but do not change it in MongoDB
        subdoc.append(kvp("ID", id));

        // Only add fields to the update document if they are provided
        // Each std::optional parameter is checked to see if it has a value.
        // If the optional has a value, it is dereferenced with * and added to the update document.
        if (type) subdoc.append(kvp("Type", *type));                  // If type is provided, add/update it
        if (status) subdoc.append(kvp("Status", *status));            // If status is provided, add/update it
        if (location) subdoc.append(kvp("Location", *location));      // If location is provided, add/update it
        if (map) subdoc.append(kvp("Map", *map));                     // If map is provided, add/update it
        if (currentRoomStatus) subdoc.append(kvp("Current Room Status", *currentRoomStatus)); // If room status is provided, add/update it
    }));

    try {
        // Perform upsert operation: update if document with ID exists, insert if not
        auto result = collection_.update_one(filter.view(), update_doc_builder.view(), mongocxx::options::update().upsert(true));
        if (result) {
            if (result->matched_count() > 0) {
                spdlog::info("Successfully updated robot data for ID: {}", id);
            } else if (result->upserted_id()) {
                // Log the ID of the new document if an insert occurred
                std::string upserted_id = result->upserted_id().value().get_oid().value.to_string();
                spdlog::info("Inserted new robot data with ID: {}", upserted_id);
            }
        } else {
            spdlog::warn("Upsert operation did not affect any document for ID: {}", id);
        }
    } catch (const mongocxx::exception& e) {
        spdlog::error("MongoDB upsert error: {}", e.what());
    }
}
