#ifndef AI_HPP
#define AI_HPP

#include <QObject>
#include <algorithm>  // std::min_element, std::max_element
#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <thread>
#include <vector>
#include "Helpers.hpp"

class Object
{
   public:
    Object(Point<int> loc, int id) : location(loc), id(id)
    {
    }
    Point<int> location;
    int id;
};

class Target : public Object
{
   public:
    Target(Point<int> loc, int id) : Object(loc, id)
    {
        killed = false;
    }
    bool killed;
};

class Agent : public Object
{
   public:
    Agent(Point<int> loc, int id) : Object(loc, id)
    {
        targets_found       = 0;
        moves_made          = 0;
        target_location     = Point<int>(2000, 2000);  // No target location when born
        last_broadcast_time = std::chrono::steady_clock::now();
        heading             = rand(1, 5);  // Get a randing heading
        if (heading == down)
            next_step = rand(left, right);
        else if (heading == up)
            next_step = rand(left, right);
        else if (heading == right)
            next_step = rand(down, up);
        else
            next_step = rand(down, up);
    }
    int targets_found;
    int moves_made;              // Number of moves made
    Point<int> target_location;  // If any target location is know it will be in this variable
    std::chrono::steady_clock::time_point last_broadcast_time;
    Direction heading;             // What direction its headed to
    Direction next_step;           // Next step it has to take
    void checkForCollisions();     // Avoid collision b/w other agents
    bool move(const Direction&);   // Move any given direction
    void update1();                // Make the next move, for scene 1
    void update2();                // Make the next move, for scene 2
    void update3();                // Make the next move, for scene 3
    void scanAreaForTargets1();    // Collect targets if any for scene 1
    void scanAreaForTargets2();    // Collect targets if any for scene 1
    void scanAreaForTargets3();    // Collect targets if any for scene 1
    bool moveTowards(Point<int>);  // Move towards this target point
    bool moveLeft(int x = 0);
    bool moveRight(int x = 0);
    bool moveDown(int y = 0);
    bool moveUp(int y = 0);
};

class Environment : public QObject
{
    Q_OBJECT
   public:
    int scenario;
    int iteration;
    Environment()
    {
    }
    void initializeEnvironment();
    void render();
    void play(const int&);
    void writeToFile();
    void clearGlobals();

   signals:
    void renderAgent(std::vector<Point<int>>, std::vector<int>);   // update/render agent
    void renderTarget(std::vector<Point<int>>, std::vector<int>);  // update/render target
    void clearScreen();
};

#endif /* AI_HPP */
