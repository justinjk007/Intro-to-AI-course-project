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
    srand((unsigned)time(0));
    int floor = 0, ceiling = 1000, range = (ceiling - floor);
    int random[4];
    for (int i = 0; i < 4; ++i) {
        random[i] = floor + int((range * rand()) / (RAND_MAX + 1.0));
    }

    this->agents.push_back(Agent(Point<int>(random[0], random[1]), 0));
    this->targets.push_back(Target(Point<int>(random[2], random[3]), 0));
}

void Environment::render()
{
    /**
     * Parse the locations and ids of each agent and target, then
     * update them one by one by calling the front signals
     */
    for (auto it = this->agents.begin(); it != this->agents.end(); ++it) {
	emit renderAgent(it->location,it->id);
    }

    for (auto it = this->targets.begin(); it != this->targets.end(); ++it) {
	emit renderTarget(it->location,it->id);
    }
}
