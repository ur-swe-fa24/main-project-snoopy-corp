#include "../../include/sim_lib/map.hpp"
#include <map>
#include <string>


Map::Map(){}
Map::Map(std::string name, std::map<std::string, std::vector<std::string>> rooms) : name(name), rooms(rooms) {}
//Map::Map(std::string name, json rooms) : name(name), rooms(rooms) {}

void Map::updateRoomCleanliness(std::string roomId, std::string cleaningStatus) {
    rooms[roomId][1] = cleaningStatus;
};


void Map::updateRoomName(std::string roomId, std::string roomName) {
    rooms[roomId][0] = roomName;
};
