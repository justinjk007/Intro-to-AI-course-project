#ifndef AI_HPP
#define AI_HPP

#include <QObject>
#include <vector>
#include "Point.hpp"

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
        killed = true;
    }
    bool killed;
};

class Agent : public Object
{
   public:
    Agent(Point<int> loc, int id) : Object(loc, id)
    {
        targetsFound = 0;
    }
    int targetsFound;
    void Update();       // Perform Logic/Physics changes-movements
    void ScanArea();     // Identify Nearby objects
    void TargetFound();  // Increment targets found
    bool canThenMoveLeft();
    bool canThenMoveRight();
    bool canThenMoveDown();
    bool canThenMoveUp();
};

class Environment : public QObject
{
    Q_OBJECT
   private:
    Point<int> boundaries[4];

public:
    Environment();
    void render();
    void play();

signals:
    void renderAgent(Point<int>, int);   // update/render agent
    void renderTarget(Point<int>, int);  // ipdate/render target
};

#endif /* AI_HPP */
