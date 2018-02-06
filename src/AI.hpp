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
    Point<int> location;
    Agent() : location(Point<int>()) {}
};

class Target
{
    Point<double> location;
    Target() : location(Point<double>()) {}
};

#endif /* AI_HPP */
