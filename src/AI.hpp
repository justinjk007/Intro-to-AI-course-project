#ifndef AI_HPP
#define AI_HPP

#include <QObject>
#include <vector>
#include "Point.hpp"

enum Direction { left, right, up, down };

double distance(Point<int>&, Point<int>&);           // Euclidean distance
Direction rand(const int&, const int&);              // Returns random number
Direction rand(const Direction&, const Direction&);  // Return random direction of the 2

class Object
{
   public:
    Object(Point<int> loc, int id) : location(loc), id(id) {}
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
        targetsFound = 0;
        // This means that there is no target location right now
        targetLocation = Point<int>(2000, 2000);
        origin         = loc;
        heading        = rand(1, 5);  // Get a randing heading
        if (heading == down)
            next_step = rand(left, right);
        else if (heading == up)
            next_step = rand(left, right);
        else if (heading == right)
            next_step = rand(down, up);
        else
            next_step = rand(down, up);
    }
    int targetsFound;
    Point<int> targetLocation;  // If any target location is know it will be in this variable
    Point<int> origin;          // Where it was born
    Direction heading;          // What direction its headed to
    Direction next_step;        // Next step it has to take
    void scanAreaForTargets();  // Collect targets if any
    void checkForCollisions();  // TODO: Implement this
    bool moveLeft();
    bool moveRight();
    bool moveDown();
    bool moveUp();
    bool move(const Direction&);  // Move any given direction
    void update();                // Make the next move, collect targets if any
};

class Environment : public QObject
{
    Q_OBJECT
   public:
    Environment();
    void render();
    void play();

   signals:
    void renderAgent(Point<int>, int);   // update/render agent
    void renderTarget(Point<int>, int);  // update/render target
    void clearScreen();
};

#endif /* AI_HPP */
