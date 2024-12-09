#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <nlohmann/json.hpp>

// Enum Class for defining the floor types
enum class FloorType{
    Wood, Tile, Carpet
};

class Map{
    private:
        std::string name; // Name of map object
        nlohmann::json rooms; // JSON representation of the rooms and the map
        int numRooms; // Number of rooms in the map

    public:
        Map();
        Map(std::string name, nlohmann::json rooms);

        std::string getName() { return name; }; // Getter for name of the map
        void setName(std::string mapName) { name = mapName; }; // Setter for name of the map

        void updateRoomCleanliness(std::string roomId, std::string cleaningStatus);
        std::string getRoomCleanliness(std::string roomId) { return rooms[roomId]["Cleaning Status"]; } // Gets the cleaning status of the room
        
        void updateRoomName(std::string roomId, std::string roomName); // Updates name of given room
        std::string getRoomName(std::string roomId) { return rooms[roomId]["Room"]; } // Get the name of given room
        bool roomExists(const std::string& roomId) const;

        int getNumRooms() { return numRooms; } // Getter for number of rooms
        std::string getFloorType(std::string roomId) { return rooms[roomId]["FloorType"]; } // Gets the floor type of given room ID
        
        // Note: that there are no methods to update/set floorType.
};

#endif // MAP_HPP

