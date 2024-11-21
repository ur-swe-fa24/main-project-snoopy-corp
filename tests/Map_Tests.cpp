#define CATCH_CONFIG_MAIN
#include "sim_lib/map.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_approx.hpp>

TEST_CASE("Map Unit Tests") {
    json roomsEx0 = {
        {"1", {{"Room", "Kitchen"}, {"Cleaning Status", "Unclean"}, {"FloorType", "Wood"}}},
        {"2", {{"Room", "Office"}, {"Cleaning Status", "Clean"}, {"FloorType", "Carpet"}}},
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "Unclean"}, {"FloorType", "Tile"}}}
    };

    std::map<std::string, std::vector<std::string>> roomsEx1 = {
        {"1" , {"kitchen", "unclean", "wood"}},
        {"2", {"office", "clean", "carpet"}},
        {"3" , {"bathroom", "unclean", "tile"}}
    };

    SECTION("Check Map getName") {
        Map map1 = Map("map1", roomsEx0);
        REQUIRE(map1.getName() == "map1");
    }

    SECTION("SetName is saved") {
        Map map2 = Map("map1", roomsEx0);
        map2.setName("hello");
        REQUIRE(map2.getName() == "hello");
    }

    SECTION("Check room cleanliness is saved") {
        Map map3 = Map("map1", roomsEx0);
        REQUIRE(map3.getRoomCleanliness("3") == "Unclean");
        map3.updateRoomCleanliness("3", "Clean");
        REQUIRE(map3.getRoomCleanliness("3") == "Clean");
    }

    SECTION("Check room name is saved") {
        Map map3 = Map("map1", roomsEx0);
        REQUIRE(map3.getRoomName("2") == "Office");
        map3.updateRoomName("3", "mega office");
        REQUIRE(map3.getRoomName("3") == "mega office");
    }

}