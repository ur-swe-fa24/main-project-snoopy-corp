#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <map>
#include <vector>
//#include <nlohmann/json.hpp>
//using json = nlohmann::json; ?

// Enum Classes
enum class FloorType{
    Wood, Tile, Carpet
};

class Map{
    private:
        std::string name; // Name of map object
        std::map<std::string, std::vector<std::string>> rooms; // Temporarily represents JSON of map
        //FloorType floorType;
        //int cleaningStatus;

    public:
        Map() {}
        Map(std::string name, std::map<std::string, std::vector<std::string>> rooms)
            : name(name), rooms(rooms) {}
        std::string getName() { return name; }
        void setName(std::string mapName) { name = mapName; }

        void updateRoomCleanliness(std::string roomId, std::string cleaningStatus) {} // Updates cleaning status of given room **string cleanliness -> int later
        std::string getRoomCleanliness(std::string roomId) { return rooms[roomId][1]; }
        
        void updateRoomName(std::string roomId, std::string roomName) {} // Updates name of given room
        std::string getRoomName(std::string roomId) { return rooms[roomId][0]; }

        // Note that there are no methods to update/set floorType.
};

#endif // MAP_HPP

// map class
// map name
// json: roomname, floortype, cleanliness
