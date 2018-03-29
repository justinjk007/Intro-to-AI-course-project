#ifndef AI_HPP
#define AI_HPP

#include <QObject>
#include <vector>
#include "Point.hpp"

class Agent
{
   public:
    Agent(Point<int> loc, int id) : location(loc), id(id)
    {
        targetsFound = 0;
    }
    int targetsFound;
    void Update();        // Perform Logic/Physics changes-movements
    void ScanArea();      // Identify Nearby objects
    void TargetFound();   // Increment targets found
    int id;               // To differentiate between agents
    Point<int> location;  // Position within environment
};

class Target
{
   public:
    Target(Point<int> loc, int owner) : location(loc), id(owner)
    {
    }
    Point<int> location;  // Position within environment
    int id;               // Which agent the target belongs to
};

class Environment : public QObject
{
    Q_OBJECT
   private:
    Point<int> boundaries[4];
    std::vector<Agent> agents;
    std::vector<Target> targets;

   public:
    Environment();
    void render();

   signals:
    void renderAgent(Point<int>, int);   // update/render agent
    void renderTarget(Point<int>, int);  // ipdate/render target
};

#endif /* AI_HPP */
