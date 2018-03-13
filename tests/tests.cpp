#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../src/Point.hpp"
#include "catch.hpp"

TEST_CASE("Testing Point class")
{
    Point<double> zero;
    Point<double> one(1, 2);
    Point<int> two(3, 4);
    REQUIRE(zero.x() == 0);
    REQUIRE(zero.y() == 0);
    REQUIRE(one.x() == 1.0);
    REQUIRE(one.y() == 2.0);
    REQUIRE(two.x() == 3);
    REQUIRE(two.y() == 4);
}
