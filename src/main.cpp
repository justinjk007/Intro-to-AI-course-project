#include <chrono>
#include <thread>
#include "Simulation.hpp"
#undef main

// This macro disables the extra cmd window popup when in Microsoft windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
    Simulation world;

    Point<int> testPoint1(200, 900);
    Point<int> testPoint2(300, 600);
    Point<int> testPoint3(400, 800);
    Point<int> testPoint4(500, 660);
    Point<int> testPoint5(0, 100);
    Point<int> testPoint6(200, 100);
    Point<int> testPoint7(23, 23);
    Point<int> testPoint8(56, 35);
    Point<int> testPoint9(99, 10);
    Point<int> testPoint10(17, 10);
    world.renderAgent(testPoint1, 0);
    world.renderAgent(testPoint2, 1);
    world.renderAgent(testPoint3, 2);
    world.renderAgent(testPoint4, 3);
    world.renderAgent(testPoint5, 4);
    world.renderTarget(testPoint6, 0);
    world.renderTarget(testPoint7, 1);
    world.renderTarget(testPoint8, 2);
    world.renderTarget(testPoint9, 3);
    world.renderTarget(testPoint10, 4);

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    return 0;
}
