#include "AI.hpp"

std::vector<Agent> g_agents;
std::vector<Target> g_targets;
const int step_size = 50;  // How many distance each agent can cover in one step

// Initialize environment
Environment::Environment()
{
    std::function<int()> rand = [=]() {
        int floor = 0, ceiling = 1000;  // Range of the random number
        return floor + std::rand() / (RAND_MAX / ceiling + floor);
    };

    for (int i = 0; i < 5; ++i) {
        g_agents.push_back(Agent(Point<int>(rand(), rand()), i));
        for (int j = 0; j < 5; ++j) {
            g_targets.push_back(Target(Point<int>(rand(), rand()), i));
        }
    }
}

void Environment::render()
{
    /**
     * Parse the locations and ids of each agent and target, then update them one
     * by one by calling the front signals
     */
    // Render targets first so they are on bottom
    // Started from the bottom now we here
    std::vector<Point<int>> agent_loc;
    std::vector<Point<int>> target_loc;
    std::vector<int> agent_id;
    std::vector<int> target_id;

    for (auto it = g_targets.begin(); it != g_targets.end(); ++it) {
        if (!it->killed) {
            // Add to render list if it not killed
            target_loc.push_back(it->location);
            target_id.push_back(it->id);
        }
    }
    for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
        agent_loc.push_back(it->location);
        agent_id.push_back(it->id);
    }
    this->clearScreen(); // Signal to clear the screen
    emit renderTarget(target_loc, target_id);
    emit renderAgent(agent_loc, agent_id);
}

void Environment::play()
{
    while (true) {
        for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            it->update();
            this->render();
        }
    }
}

bool Agent::moveRight()
{
    if ((this->location.x() + step_size) <= 1000) {
        this->location.addX(step_size);
        return true;
    } else
        return false;
}

bool Agent::moveLeft()
{
    if ((this->location.x() - step_size) >= 0) {
        this->location.addX(-step_size);
        return true;
    } else
        return false;
}

bool Agent::moveDown()
{
    if ((this->location.y() + step_size) <= 1000) {
        this->location.addY(step_size);
        return true;
    } else
        return false;
}

bool Agent::moveUp()
{
    if ((this->location.y() - step_size) >= 0) {
        this->location.addY(-step_size);
        return true;
    } else
        return false;
}

void Agent::scanAreaForTargets()
{
    /**
     * If there are targets nearby mark them as killed, which will remove it from
     * rendering. Also ++targetsFound of the agent.
     */
    int radar_range = 50;
    for (auto it = g_targets.begin(); it != g_targets.end(); ++it)
        // If a target has the same id and is nearby get it
        if (it->id == this->id && distance(it->location, this->location) <= radar_range) {
            it->killed = true;
            this->targetsFound++;
        }
}

void Agent::checkForCollisions()
{
    /**
     * If there are any other agents nearby move away from them or do
     * some maneuver to avoid collision
     */
    int radar_range = 100;
    for (auto it = g_agents.begin(); it != g_agents.end(); ++it)
        if (it->id != this->id && distance(it->location, this->location) <= radar_range) {
            if (move(this->heading))
                ;  // When collision is predicted take a step in the heading direction, if it can't
                   // make that step move in the opposite direction of the heading direction
            else
                move(opposite(this->heading));
        }
}

void Agent::update()
{
    /*
     * Each agent gets a random heading direction so it knows which direction is
     * it going in general and random next_step direction.(done during
     * construction). If its heading down for example each next step will be left
     * or right, until it can't move in that direction anymore then it will move
     * one step in direction of heading and make the next_step to opposite
     * direction. It moves right until it can't move down. Then it will go in the
     * opposite direction(up) and move to the upper corners. Since agents never
     * run out of fuel it does this over and over util one of the agents finds
     * all the targets.
     */
    if (move(this->next_step)) {
        this->scanAreaForTargets();
        this->checkForCollisions();  // TODO: Implement this
    } else {
        this->next_step = opposite(this->next_step);
        if (!move(this->heading)) this->heading = opposite(this->heading);
    }
}

bool Agent::move(const Direction& direction)
{
    /**
     * Move to the given direction if possible, return false if you can't move
     * anymore.
     */
    switch (direction) {
        case left:
            return this->moveLeft();
        case right:
            return this->moveRight();
        case down:
            return this->moveDown();
        default:
            return this->moveUp();
    }
}

bool compare(Point<int>& lhs, Point<int>& rhs)
{
    /**
     * Return true of both points are equal
     */
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
}

double distance(Point<int>& a, Point<int>& b)
{
    /**
     * Return the euclidean distance between the points
     */
    double diff_x = pow(b.x() - a.x(), 2);
    double diff_y = pow(b.y() - a.y(), 2);
    return sqrt(diff_y + diff_x);
}

Direction rand(const int& floor, const int& ceiling)
{
    /**
     * Return a random direction
     */
    int val = floor + std::rand() / (RAND_MAX / ceiling + floor);
    switch (val) {
        case 1:
            return right;
        case 2:
            return left;
        case 3:
            return up;
        default:
            return down;
    }
}

Direction rand(const Direction& a, const Direction& b)
{
    /**
     * Return a random direction of the two given ones
     */
    int val = 1 + std::rand() / (RAND_MAX / 2 + 1);
    if (val == 1)
        return a;
    else
        return b;
}

Direction opposite(const Direction& direction)
{
    /**
     * Returns the opposite direction of the given one
     */
    switch (direction) {
        case left:
            return right;
        case right:
            return left;
        case down:
            return up;
        default:
            return down;
    }
}
