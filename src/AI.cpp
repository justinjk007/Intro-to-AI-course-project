#include "AI.hpp"

std::vector<Agent> g_agents;
std::vector<Target> g_targets;
std::list<Target> public_channel;

const int step_size = 50;  // How many distance each agent can cover in one step

// Initialize environment
Environment::Environment()
{
    std::function<int()> rand = [=]() {
        int floor = 0, ceiling = 1000;  // Range of the random number
        return floor + std::rand() / (RAND_MAX / ceiling + floor);
    };

    for (int i = 0; i < 1; ++i) {
        g_agents.push_back(Agent(Point<int>(rand(), rand()), i));
        for (int j = 0; j < 5; ++j) {
            g_targets.push_back(Target(Point<int>(rand(), rand()), i));
        }
    }
}

void Environment::render()
{
    /**
     * Parse the locations and ids of each agent and target, then update them one by one by calling
     * the front signals
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
    emit clearScreen();  // Signal to clear the screen
    emit renderTarget(target_loc, target_id);
    emit renderAgent(agent_loc, agent_id);
}

void Environment::play()
{
    while (true) {
        for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
            // WARNING!!! If the delay is considerably less than 50ms it will use more CPU and even
            // make your system unresponsive
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            // it->update();  // make the agents next move
            it->moveTowards(Point<int>(500, 500));
            // FIXME: Moving to points in the middle seems to be breaking
            this->render();
        }
    }
}

bool Agent::moveRight()
{
    if ((this->location.x() + step_size) <= 1000) {
        this->location.addX(step_size);
        std::cout << "right\n";
        return true;
    } else {
        std::cout << "can't move right\n";
        return false;
    }
}

bool Agent::moveLeft()
{
    if ((this->location.x() - step_size) >= 0) {
        this->location.addX(-step_size);
        std::cout << "left\n";
        return true;
    } else {
        std::cout << "can't move left\n";
        return false;
    }
}

bool Agent::moveDown()
{
    if ((this->location.y() + step_size) <= 1000) {
        this->location.addY(step_size);
        std::cout << "down\n";
        return true;
    } else {
        std::cout << "can't move down\n";
        return false;
    }
}

bool Agent::moveUp()
{
    if ((this->location.y() - step_size) >= 0) {
        this->location.addY(-step_size);
        std::cout << "up\n";
        return true;
    } else {
        std::cout << "can't move up\n";
        return false;
    }
}

void Agent::scanAreaForTargets()
{
    /**
     * If there are targets nearby mark them as killed, which will remove it from rendering. Also
     * ++targetsFound of the agent. Return false if nothing is collected
     */
    int radar_range = 55;
    for (auto it = g_targets.begin(); it != g_targets.end(); ++it)
        // If a target has the same id and is nearby get it
        if (it->id == this->id && distance(it->location, this->location) <= radar_range) {
            it->killed = true;
            this->targets_found++;
        }
}

void Agent::checkForCollisions()
{
    /**
     * If there are any other agents nearby move away from them or do some maneuver to avoid
     * collision
     */
    int collision_range = 120;
    for (auto it = g_agents.begin(); it != g_agents.end(); ++it)
        if (it->id != this->id && distance(it->location, this->location) <= collision_range) {
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
     * Each agent gets a random heading direction so it knows which direction is it going in general
     * and random next_step direction.(done during construction). If its heading down for example
     * each next step will be left or right, until it can't move in that direction anymore then it
     * will move one step in direction of heading and make the next_step to opposite direction. It
     * moves right until it can't move down. Then it will go in the opposite direction(up) and move
     * to the upper corners. Since agents never run out of fuel it does this over and over util one
     * of the agents finds all the targets.
     */

    // Lambda storing the default_behavior
    std::function<void()> default_behavior = [=]() {
        if (move(this->next_step)) {
            this->scanAreaForTargets();
            this->checkForCollisions();
        } else {
            this->next_step = opposite(this->next_step);
            if (!move(this->heading)) {
                this->heading = opposite(this->heading);
            } else {
                // If can move check these
                this->scanAreaForTargets();
                this->checkForCollisions();
            }
        }
    };

    Point<int> nullpoint(2000, 2000);
    if (!compare(this->target_location, nullpoint)) {  // if target_location != nullpoint
        // If valid target location is known move towards it
        if (!moveTowards(target_location)) {
            // If it can't move to that location then delete the target location
            this->target_location = nullpoint;
        }
        this->scanAreaForTargets();
        this->checkForCollisions();
    } else {
        // Check if there is any known targets in the public channel
        for (auto it = public_channel.begin(); it != public_channel.end(); ++it) {
            if (it->id == this->id) {
                // This is our target so set it as target_location
                this->target_location = it->location;
                it                    = public_channel.erase(it);  // Remove from channel
                default_behavior();                                // Make the default maneuver
            } else
                default_behavior();  // Make the default maneuver
        }
    }
}

bool Agent::move(const Direction& direction)
{
    /**
     * Move to the given direction if possible, return false if you can't move anymore.
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

bool Agent::moveTowards(Point<int> destination)
{
    /**
     * This method will try to move towards the given destination, if it can't it will return false.
     */
    int radar_range = 50;
    int xy_range = 50;
    if ((distance(this->location, destination) < radar_range)) {
        std::cout << "Target reached\n";
        return false;  // We are at the location so return false forgetting about this location
    }

    if ((destination.x() - this->location.x()) < xy_range && moveLeft()) {
	std::cout << "left,mradar: " << destination.x() - this->location.x() << "\n";
	return true;
    } else if ((destination.x() - this->location.x()) > xy_range && moveRight()){
	std::cout << "right,radar: " << destination.x() - this->location.x() << "\n";
	return true;
    }
    else if ((destination.y() - this->location.y()) < xy_range && moveUp())
        return true;
    else if ((destination.y() - this->location.y()) > xy_range && moveDown())
        return true;
    else {
        return false;  // It might be a fake point which agent can't reach so false
    }
}

bool compare(Point<int> lhs, Point<int> rhs)
{
    /**
     * Return true of both points are equal
     */
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
}

double distance(Point<int> a, Point<int> b)
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
