#include <chrono>
#include <thread>
#include "Simulation.hpp"

int main()
{
    Simulation world;

    Point<int> testPoint1(200, 900);
    Point<int> testPoint2(300, 600);
    Point<int> testPoint3(400, 800);
    Point<int> testPoint4(500, 660);
    Point<int> testPoint5(0, 100);

    world.renderAgent(testPoint1, 0);
    world.renderAgent(testPoint2, 1);
    world.renderTarget(testPoint3, 0);
    world.renderTarget(testPoint4, 1);
    world.renderTarget(testPoint5, 4);

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return 0;
}
