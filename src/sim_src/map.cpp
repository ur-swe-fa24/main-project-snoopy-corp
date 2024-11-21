#include "../../include/sim_lib/map.hpp"
#include <map>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


Map::Map(){}
//Map::Map(std::string name, std::map<std::string, std::vector<std::string>> rooms) : name(name), rooms(rooms) {}
Map::Map(std::string name, json rooms) : name(name), rooms(rooms) {}

void Map::updateRoomCleanliness(std::string roomId, std::string cleaningStatus) {
    rooms[roomId]["Cleaning Status"] = cleaningStatus;
};


void Map::updateRoomName(std::string roomId, std::string roomName) {
    rooms[roomId]["Room"] = roomName;
};

bool Map::roomExists(const std::string& roomId) const {
    return rooms.contains(roomId); // Checks if the key exists in the JSON object
}
