#include "../include/map.hpp"
#include <map>
#include <string>
#include <vector>
#include <iostream>


int main() {
    std::map<std::string, std::vector<std::string>> roomsEx1 = {
        {"1" , {"kitchen", "1", "wood"}},
        {"2", {"office", "5", "carpet"}},
        {"3" , {"bathroom", "7", "tile"}}
    };

    Map map1 = Map("UFA476", roomsEx1);
    
    map1.setName("new name");
    std::cout << "Map new name: " << map1.getName() << std::endl;

    map1.updateRoomCleanliness("2", "4");
    std::cout << "Office new cleaning status: " << map1.getName() << std::endl;

}
