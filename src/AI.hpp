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
	// To differentiate between agents
	int agentID;
	// Position within environment
    Point<int> location;
	// Default constructor
    Agent() : location(Point<int>()) {}

	// Perform Logic/Physics changes-movements
	void Update();
	// Identify Nearby objects
	void ScanArea();
	// Increment targets found
	void TargetFound();

private:
	// Might not need this counter, use for determinng end condition
	int targetsFound = 0;
};

class Target
{
public:
	// Position within environment
    Point<double> location;
	// Which agent the target belongs to
	int ownerAgent;
	// Default constructor
    Target() : location(Point<double>()) {}

	// Perform Logic/Physics changes
	void Update();

private:
	// Use to determine when to stop rendering target
	bool pickedUp = false;
};

#endif /* AI_HPP */
