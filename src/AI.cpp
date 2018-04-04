#include "AI.hpp"

std::vector<Agent> g_agents;
std::vector<Target> g_targets;
std::list<Target> public_channel;
std::list<Target> private_channel;

const int step_size             = 50;  // How many distance each agent can cover in one step
const int delay_after_each_step = 50;  // WARNING!!! If the delay is considerably less than 50ms it
                                       // will use more CPU and even make your system unresponsive

// Initialize environment
void Environment::initializeEnvironment()
{
    /**
     * This method is used instead of a constructor because we have to use the same environemnt for
     * multiple iterations and this means the connection b/w the front end is not killed
     */
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

void Environment::play(const int& scene)
{
    bool run_condition = true;
    this->scenario     = scene;
    if (scene == 1) {
        while (run_condition) {
            for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
                it->update1();     // Make the agents next move
                it->moves_made++;  // Count the current move
                this->render();
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_after_each_step));
                if (it->targets_found == 5) {
                    run_condition = false;
                }
            }
        }
    } else if (scene == 2) {
        int found = 0;
        while (run_condition) {
            found = 0;
            for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
                it->update2();     // Make the agents next move
                it->moves_made++;  // Count the current move
                this->render();
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_after_each_step));
                found += it->targets_found;
            }
            if (found == 25) {
                run_condition = false;
            }
        }
    } else {  // Scenario 3
        while (run_condition) {
            for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
                it->update3();     // Make the agents next move
                it->moves_made++;  // Count the current move
                this->render();
                std::this_thread::sleep_for(std::chrono::milliseconds(delay_after_each_step));
                if (it->targets_found == 5) run_condition = false;
            }
        }
    }
}

void Environment::clearGlobals()
{
    /**
     * This fucntion will clear the globals before the next iteration
     */
    g_agents.clear();         // clear vector
    g_targets.clear();        // clear vector
    public_channel.clear();   // clear list
    private_channel.clear();  // clear list
}

void Environment::writeToFile()
{
    /**
     * Write iteration data to file appending it in csv format
     */
    double happiness[5]       = {0.0};
    double competitiveness[5] = {0.0};
    double happiness_sum      = 0.0;  // Sum
    double happiness_ave      = 0.0;  // Mean
    double happiness_sd       = 0.0;  // Standard Deviation
    double happiness_max      = 0.0;  // Maximum happiness
    double happiness_min      = 0.0;  // Minimum happiness
    // Calculate happiness for all agents
    for (auto it = g_agents.begin(); it != g_agents.end(); it++) {
        happiness[it->id] = it->targets_found / (it->moves_made + 1.0);
        happiness_sum += happiness[it->id];
    }
    happiness_ave             = happiness_sum / 5.0;
    happiness_min             = *std::min_element(happiness, happiness + 5);
    happiness_max             = *std::max_element(happiness, happiness + 5);
    double happiness_variance = 0;
    for (int i = 0; i < 5; i++) {
        happiness_variance += (happiness[i] - happiness_ave) * (happiness[i] - happiness_ave);
    }
    happiness_variance /= 5;
    happiness_sd = sqrt(happiness_variance);
    for (int i = 0; i < 5; i++) {
        competitiveness[i] = (happiness[i] - happiness_min) / (happiness_max - happiness_min);
    }
    std::ofstream file;
    file.open("G16_1.csv", std::ios_base::app);
    if (!file.is_open()) {
        std::cout << "File opening failed\n";
        exit(1);
    }
    // Scene, Iter, Agent, #Targets, Steps, Happ, Max, Min, Ave, SD, competitiveness
    for (auto it = g_agents.begin(); it != g_agents.end(); ++it) {
        file << this->scenario << "," << this->iteration << "," << it->id << ","
             << it->targets_found << "," << it->moves_made << "," << happiness[it->id] << ","
             << happiness_max << "," << happiness_min << "," << happiness_ave << "," << happiness_sd
             << "," << competitiveness[it->id] << "\n";
    }
    file.close();
}

bool Agent::moveRight(int x)
{
    /**
     * The parameter x is the destination x the agent is trying to reach so if moving to that means
     * making a move less than 50 units move to x.
     */
    std::function<bool()> default_behavior = [=]() {
        if ((this->location.x() + step_size) <= 1000) {
            this->location.addX(step_size);
            return true;
        } else {
            return false;
        }
    };

    if (x == 0) {  // Default
        return default_behavior();
    } else {
        int new_step_size = x - this->location.x();
        if (new_step_size <= step_size) {
            if ((this->location.x() + new_step_size) <= 1000) {
                this->location.addX(new_step_size);
                return true;
            } else {
                return false;
            }
        } else {  // If the wanted step size is greater than usual step size
            return default_behavior();
        }
    }
}

bool Agent::moveLeft(int x)
{
    std::function<bool()> default_behavior = [=]() {
        if ((this->location.x() - step_size) >= 0) {
            this->location.addX(-step_size);
            return true;
        } else {
            return false;
        }
    };

    if (x == 0) {  // Default
        return default_behavior();
    } else {
        int new_step_size = this->location.x() - x;
        if (new_step_size <= step_size) {
            if ((this->location.x() - new_step_size) >= 0) {
                this->location.addX(-new_step_size);
                return true;
            } else {
                return false;
            }
        } else {  // If the wanted step size is greater than usual step size
            return default_behavior();
        }
    }
}

bool Agent::moveDown(int y)
{
    /**
     * The parameter y is the destination y the agent is trying to reach so if moving to
     * that means making a move less than 50 units move to y
     */
    std::function<bool()> default_behavior = [=]() {
        if ((this->location.y() + step_size) <= 1000) {
            this->location.addY(step_size);
            return true;
        } else {
            return false;
        }
    };

    if (y == 0) {  // Default
        return default_behavior();
    } else {
        int new_step_size = y - this->location.y();
        if (new_step_size <= step_size) {
            if ((this->location.y() + new_step_size) <= 1000) {
                this->location.addY(new_step_size);
                return true;
            } else {
                return false;
            }
        } else {
            return default_behavior();
        }
    }
}

bool Agent::moveUp(int y)
{
    std::function<bool()> default_behavior = [=]() {
        if ((this->location.y() - step_size) >= 0) {
            this->location.addY(-step_size);
            return true;
        } else {
            return false;
        }
    };

    if (y == 0) {  // Default
        return default_behavior();
    } else {
        int new_step_size = this->location.y() - y;
        if (new_step_size <= step_size) {
            if ((this->location.y() - new_step_size) >= 0) {
                this->location.addY(-new_step_size);
                return true;
            } else {
                return false;
            }
        } else {
            return default_behavior();
        }
    }
}

void Agent::scanAreaForTargets1()
{
    /**
     * If there are targets nearby mark them as killed, which will
     * remove it from rendering.  Also targetsFound++ of the
     * agent. Return false if nothing is collected. This is for scenario
     * 1 where public channel communication is used.
     */
    int range = 55;
    auto t    = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::steady_clock::now() - this->last_broadcast_time)
                 .count();  // Time between last broadcast

    for (auto it = g_targets.begin(); it != g_targets.end(); ++it) {
        if (it->id == this->id && distance(it->location, this->location) <= range) {
            // If a target has the same id and is nearby get it
            if (!it->killed) {
                it->killed = true;
                this->targets_found++;
            }
        } else if (it->id != this->id && distance(it->location, this->location) <= range &&
                   t > 1500) {
            // If not our target broadcast in the public channel, lie 1/4 times
            if (rand_3_by_4()) {
                this->last_broadcast_time = std::chrono::steady_clock::now();
                public_channel.push_back(*it);
            } else {
                // Lies
                Target foo(it->location, it->id);
                foo.location.addX(200);
                foo.location.addY(-200);
                this->last_broadcast_time = std::chrono::steady_clock::now();
                public_channel.push_back(foo);
            }
        }
    }
}

void Agent::scanAreaForTargets2()
{
    /**
     * This is for scenario 2 where public and private channels are used
     */
    int range = 55;
    auto t    = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::steady_clock::now() - this->last_broadcast_time)
                 .count();  // Time between last broadcast

    for (auto it = g_targets.begin(); it != g_targets.end(); ++it) {
        if (it->id == this->id && distance(it->location, this->location) <= range) {
            // If a target has the same id and is nearby get it
            if (!it->killed) {
                it->killed = true;
                this->targets_found++;
            }
        } else if (it->id != this->id && distance(it->location, this->location) <= range &&
                   t > 1500) {
            // If not our target broadcast in the public channel, lie 1/4 times
            this->last_broadcast_time = std::chrono::steady_clock::now();
            private_channel.push_back(*it);
        }
    }
}

void Agent::scanAreaForTargets3()
{
    /**
     * This is for scenario 3 where only private channels are used
     */
    int range = 55;
    auto t    = std::chrono::duration_cast<std::chrono::milliseconds>(
                 std::chrono::steady_clock::now() - this->last_broadcast_time)
                 .count();  // Time between last broadcast

    for (auto it = g_targets.begin(); it != g_targets.end(); ++it) {
        if (it->id == this->id && distance(it->location, this->location) <= range) {
            // If a target has the same id and is nearby get it
            if (!it->killed) {
                it->killed = true;
                this->targets_found++;
            }
        } else if (it->id != this->id && distance(it->location, this->location) <= range &&
                   t > 3000) {
            this->last_broadcast_time = std::chrono::steady_clock::now();
            private_channel.push_back(*it);
        }
    }
}

void Agent::checkForCollisions()
{
    /**
     * If there are any other agents nearby move away from them or do some maneuver
     * to avoid collision
     */
    // int collision_range = 50;
    // for (auto it = g_agents.begin(); it != g_agents.end(); ++it)
    //     if (it->id != this->id && distance(it->location, this->location) <= collision_range) {
    //         if (move(this->heading))
    //             ;  // When collision is predicted take a step in the heading
    //                // direction, if it can't make that step move in the opposite
    //                // direction of the heading direction
    //         else
    //             move(opposite(this->heading));
    //     }
}

void Agent::update1()
{
    /*
     * Each agent gets a random heading direction so it knows which direction is it
     * going in general and random next_step direction.(done during construction).
     * If its heading down for example each next step will be left or right, until
     * it can't move in that direction anymore then it will move one step in
     * direction of heading and make the next_step to opposite direction. It moves
     * right until it can't move down. Then it will go in the opposite direction(up)
     * and move to the upper corners. Since agents never run out of fuel it does
     * this over and over util one of the agents finds all the targets.
     */

    // Lambda storing the default_behavior
    std::function<void()> default_behavior = [=]() {
        if (move(this->next_step)) {
            this->scanAreaForTargets1();
            this->checkForCollisions();
        } else {
            this->next_step = opposite(this->next_step);
            if (!move(this->heading)) {
                this->heading = opposite(this->heading);
            } else {
                // If can move check these
                this->scanAreaForTargets1();
                this->checkForCollisions();
            }
        }
    };

    Point<int> nullpoint(2000, 2000);
    if (!compare(this->target_location, nullpoint)) {  // if target_location != nullpoint
        if (!moveTowards(target_location)) {           // If valid target location is known move
                                                       // towards it
            this->target_location = nullpoint;         // If it can't move here then delete it
        }
        this->scanAreaForTargets1();
        this->checkForCollisions();
    } else {
        // Check if there is any known targets in the public channel
        if (!public_channel.empty()) {
            auto it = public_channel.begin();
            for (; it != public_channel.end();) {
                if (it->id == this->id) {
                    this->target_location = it->location;              // Set it as new target
                    it                    = public_channel.erase(it);  // Remove from channel
                    default_behavior();                                // Do the default maneuver
                } else {
                    ++it;
                }
            }
            default_behavior();  // We did't find any targets so do the default
        } else
            default_behavior();  // Do the default maneuver
    }
}

void Agent::update2()
{
    // Lambda storing the default_behavior
    std::function<void()> default_behavior = [=]() {
        if (move(this->next_step)) {
            this->scanAreaForTargets2();
            this->checkForCollisions();
        } else {
            this->next_step = opposite(this->next_step);
            if (!move(this->heading)) {
                this->heading = opposite(this->heading);
            } else {
                // If can move check these
                this->scanAreaForTargets2();
                this->checkForCollisions();
            }
        }
    };

    Point<int> nullpoint(2000, 2000);
    if (!compare(this->target_location, nullpoint)) {  // if target_location != nullpoint
        if (!moveTowards(target_location)) {           // If valid target location is known move
                                                       // towards it
            this->target_location = nullpoint;         // If it can't move here then delete it
        }
        this->scanAreaForTargets2();
        this->checkForCollisions();
    } else {
        // Check if there is any known targets in the public or privat te channels
        if (!private_channel.empty()) {
            auto it = private_channel.begin();
            for (; it != private_channel.end();) {
                if (it->id == this->id) {
                    this->target_location = it->location;               // Set it as new target
                    it                    = private_channel.erase(it);  // Remove from channel
                    default_behavior();                                 // Do the default maneuver
                } else {
                    ++it;
                }
            }
            default_behavior();  // We did't find any targets so do the default
        } else if (!public_channel.empty()) {
            auto it = public_channel.begin();
            for (; it != public_channel.end();) {
                if (it->id == this->id) {
                    this->target_location = it->location;              // Set it as new target
                    it                    = public_channel.erase(it);  // Remove from channel
                    default_behavior();                                // Do the default maneuver
                } else {
                    ++it;
                }
            }
            default_behavior();  // We did't find any targets so do the default
        } else
            default_behavior();  // Do the default maneuver
    }
}

void Agent::update3()
{
    // Lambda storing the default_behavior
    std::function<void()> default_behavior = [=]() {
        if (move(this->next_step)) {
            this->scanAreaForTargets3();
            this->checkForCollisions();
        } else {
            this->next_step = opposite(this->next_step);
            if (!move(this->heading)) {
                this->heading = opposite(this->heading);
            } else {
                // If can move check these
                this->scanAreaForTargets3();
                this->checkForCollisions();
            }
        }
    };

    Point<int> nullpoint(2000, 2000);
    if (!compare(this->target_location, nullpoint)) {  // if target_location != nullpoint
        if (!moveTowards(target_location)) {           // If valid target location is known move
                                                       // towards it
            this->target_location = nullpoint;         // If it can't move here then delete it
        }
        this->scanAreaForTargets3();
        this->checkForCollisions();
    } else {
        // Check if there is any known targets in the public channel
        if (!private_channel.empty()) {
            auto it = private_channel.begin();
            for (; it != private_channel.end();) {
                if (it->id == this->id) {
                    this->target_location = it->location;               // Set it as new target
                    it                    = private_channel.erase(it);  // Remove from channel
                    default_behavior();                                 // Do the default maneuver
                } else {
                    ++it;
                }
            }
            default_behavior();  // We did't find any targets so do the default
        } else
            default_behavior();  // Do the default maneuver
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

bool Agent::moveTowards(Point<int> destination)
{
    /**
     * This method will try to move towards the given destination, if it can't it
     * will return false.
     */
    int radar_range = 50;
    int xy_range    = 50;
    if ((distance(this->location, destination) < radar_range)) {
        return false;  // We are at the location so return false forgetting about
                       // this location
    }

    int val1 = destination.x() - this->location.x();
    int val2 = destination.y() - this->location.y();
    if (val1 < xy_range && val1 != 0 && moveLeft(destination.x()))
        return true;
    else if (val1 > xy_range && val1 != 0 && moveRight(destination.x()))
        return true;
    else if (val2 < xy_range && val2 != 0 && moveUp(destination.y()))
        return true;
    else if (val2 > xy_range && val2 != 0 && moveDown(destination.y()))
        return true;
    else {
        return false;  // It might be a fake point which agent can't reach so false
    }
}
