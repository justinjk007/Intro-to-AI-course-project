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
	// Keep track of targets found
	Target * myTargets[5];
	// Position within environment
    Point<int> location;
	// Default constructor
    Agent() : location(Point<int>()) {}

	// Not sure if we'll need this one yet
	void SetAgentLocation(Point<int> loc);
	// Perform Logic/Physics changes-movements
	void Update();
	// Identify Nearby objects
	void ScanArea();
	// Increment targets found
	void TargetFound();
	// Render object
	void Render();

private:
	// Might not need this counter, use for determinng end condition
	int targetsFound = 0;
	// List of all agents
	Agent* allAgents[5];
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

	// Not sure if we'll need this one yet
	void SetTargetLocation(Point<int> loc);
	// Perform Logic/Physics changes
	void Update();
	// Render objects
	void Render();

private:
	// Use to determine when to stop rendering target
	bool pickedUp = false;
	// List of all targets
	Target * allTargets[25];
};

#endif /* AI_HPP */
