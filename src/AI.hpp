#ifndef AI_HPP
#define AI_HPP

#include "Point.hpp"

class Environment
{
    Point<int> boundaries[4];
    Environment()
    {
        this->boundaries[0] = Point<int>();
        this->boundaries[1] = Point<int>();
        this->boundaries[2] = Point<int>();
        this->boundaries[3] = Point<int>();
    }
};

class Agent
{
public:
    int agentID;                         // To differentiate between agents
    Point<int> location;                 // Position within environment
    Agent() : location(Point<int>()) {}  // Default constructor
    void Update();                       // Perform Logic/Physics changes-movements
    void ScanArea();                     // Identify Nearby objects
    void TargetFound();                  // Increment targets found

   private:
    int targetsFound;  // Might not need this counter, use for determinng end condition
};

class Target
{
   public:
    Point<double> location;  // Position within environment
    int ownerAgent;          // Which agent the target belongs to
    Target() : location(Point<double>()) {}
    void Update();  // Perform Logic/Physics changes
   private:
    bool pickedUp;  // Use to determine when to stop rendering target
};

#endif /* AI_HPP */
