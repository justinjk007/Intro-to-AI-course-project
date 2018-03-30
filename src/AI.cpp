#include "AI.hpp"
#include <chrono>
#include <ctime>
#include <string>
#include <thread>

std::vector<Agent> g_agents;
std::vector<Target> g_targets;

// Initialize environment
Environment::Environment()
{
    boundaries[0] = Point<int>(0, 0);        // Top left corner
    boundaries[1] = Point<int>(1000, 0);     // Top right corner
    boundaries[2] = Point<int>(1000, 1000);  // Bottom right corner
    boundaries[3] = Point<int>(0, 1000);     // Bottom left corner

    std::srand(std::time(nullptr));
    int floor = 0, ceiling = 1000;  // Range of the random numbers generated
    int random[2];
    for (int i = 0; i < 1; ++i) {
        random[0] = floor + std::rand() / (RAND_MAX / ceiling + floor);
        random[1] = floor + std::rand() / (RAND_MAX / ceiling + floor);
        // Agent one(Point<int>(random[0], random[1]), 0);
        Agent one(Point<int>(0, 0), 0);
        Target two(Point<int>(random[1], random[0]), 0);
        g_agents.push_back(one);
        g_targets.push_back(two);
        // Add a second loop here when you need more than 1 target per agent
    }
}

void Environment::render()
{
    /**
     * Parse the locations and ids of each agent and target, then
     * update them one by one by calling the front signals
     */
    this->clearScreen();
    for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
        emit renderAgent(it->location, it->id);
    }
    for (auto it = g_targets.begin(); it != g_targets.end(); ++it) {
        emit renderTarget(it->location, it->id);
    }
}

void Environment::render2()
{
    /**
     * Parse the locations and ids of each agent and target, then
     * update them one by one by calling the front signals
     */
    this->clearScreen();
    for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
        emit renderTarget(it->location, it->id);
    }
    for (auto it = g_targets.begin(); it != g_targets.end(); ++it) {
        emit renderAgent(it->location, it->id);
    }
}

void Environment::play()
{
    auto it = g_agents.begin();
    for (int i = 0; i < 100; ++i) {
        it->moveRight();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->render();
    }
}

bool Agent::moveRight()
{
    if ((this->location.x() + 10) <= 1000) {
        this->location.addX(10);
        return true;
    } else
        return false;
}

bool Agent::moveLeft()
{
    if ((this->location.x() - 10) >= 0) {
        this->location.addX(-10);
        return true;
    } else
        return false;
}

bool Agent::moveDown()
{
    if ((this->location.y() + 10) <= 1000) {
        this->location.addY(10);
        return true;
    } else
        return false;
}

bool Agent::moveUp()
{
    if ((this->location.y() - 10) >= 0) {
        this->location.addY(-10);
        return true;
    } else
        return false;
}
