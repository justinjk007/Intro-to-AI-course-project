#include <chrono>
#include <thread>
#include "Simulation.hpp"

int main()
{
    Simulation world;
    // setup objects here, call constructors etc...
    Point<int> testPoint(3, 4);
    int ID = 10;
    world.Render(testPoint, ID);
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return 0;
}
