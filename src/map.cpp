#include "../include/map.hpp"
#include <map>
#include <string>

void Map::updateRoomCleanliness(std::string roomId, int cleaningStatus) {
    rooms[roomId][1] = cleaningStatus;
};


void Map::updateRoomName(std::string roomId, std::string roomName) {
    rooms[roomId][0] = roomName;
};
