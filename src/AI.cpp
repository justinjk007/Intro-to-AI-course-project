#include "AI.hpp"
#include <ctime>
#include <string>

// Initialize environment
Environment::Environment()
{
    boundaries[0] = Point<int>(0, 0);        // Top left corner
    boundaries[1] = Point<int>(1000, 0);     // Top right corner
    boundaries[2] = Point<int>(1000, 1000);  // Bottom right corner
    boundaries[3] = Point<int>(0, 1000);     // Bottom left corner

    // Get some random numbers for positions
    std::srand(std::time(nullptr));
    int floor = 0, ceiling = 1000;
    int random[2];
    for (int i = 0; i < 1; ++i) {
        random[0] = floor + std::rand() / (RAND_MAX / ceiling + floor);
        random[1] = floor + std::rand() / (RAND_MAX / ceiling + floor);
        Agent one(Point<int>(random[0], random[1]), 0);
        Target two(Point<int>(random[1], random[0]), 0);
        this->agents.push_back(one);
        this->targets.push_back(two);
        // Add a second loop here when you need more than 1 target per agent
    }
}

void Environment::render()
{
    /**
     * Parse the locations and ids of each agent and target, then
     * update them one by one by calling the front signals
     */
    for (auto it = this->agents.begin(); it != this->agents.end(); ++it) {
        emit renderAgent(it->location, it->id);
    }
    for (auto it = this->targets.begin(); it != this->targets.end(); ++it) {
        emit renderTarget(it->location, it->id);
    }
}

void Agent::Update() {}
