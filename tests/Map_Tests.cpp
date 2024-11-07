#define CATCH_CONFIG_MAIN
#include "../include/sim_lib/map.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_approx.hpp>

TEST_CASE("Map Unit Tests") {
    std::map<std::string, std::vector<std::string>> roomsEx1 = {
        {"1" , {"kitchen", "unclean", "wood"}},
        {"2", {"office", "clean", "carpet"}},
        {"3" , {"bathroom", "unclean", "tile"}}
    };

    SECTION("Check Map getName") {
        Map map1 = Map("map1", roomsEx1);
        REQUIRE(map1.getName() == "map1");
    }

    SECTION("SetName is saved") {
        Map map2 = Map("map1", roomsEx1);
        map2.setName("hello");
        REQUIRE(map2.getName() == "hello");
    }

    SECTION("Check room cleanliness is saved") {
        Map map3 = Map("map1", roomsEx1);
        REQUIRE(map3.getRoomCleanliness("3") == "unclean");
        map3.updateRoomCleanliness("3", "clean");
        REQUIRE(map3.getRoomCleanliness("3") == "clean");
    }

    SECTION("Check room name is saved") {
        Map map3 = Map("map1", roomsEx1);
        REQUIRE(map3.getRoomName("2") == "office");
        map3.updateRoomName("3", "mega office");
        REQUIRE(map3.getRoomName("3") == "mega office");
    }

}