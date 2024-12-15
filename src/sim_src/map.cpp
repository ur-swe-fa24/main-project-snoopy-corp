#include "../../include/sim_lib/map.hpp"

Map::Map(){}
Map::Map(std::string name, json rooms) : name(name), rooms(rooms), numRooms(rooms.size()) {}

// Updates cleaning status of given room id and cleaning status
void Map::updateRoomCleanliness(std::string roomId, std::string cleaningStatus) {
    rooms[roomId]["Cleaning Status"] = cleaningStatus;
};

// Updates the name of the room of the given roomId with the given roomName
void Map::updateRoomName(std::string roomId, std::string roomName) {
    rooms[roomId]["Room"] = roomName;
};

// Checks whether the given roomId exists within the rooms JSON and returns that truth value
bool Map::roomExists(const std::string& roomId) const {
    return rooms.contains(roomId); // Checks if the key exists in the JSON object
}

#include <iostream>
void Map::resetRoomCleanliness(){
    std::mt19937 gen(std::random_device{}()); // Random generator with seed
    std::uniform_int_distribution<int> distrib(0, 8); // Range [0, 8]
    for (nlohmann::json& room : rooms){
        room["Cleaning Status"] = std::to_string(distrib(gen));
    }
    std::cout << rooms.dump(4) << std::endl;
}
