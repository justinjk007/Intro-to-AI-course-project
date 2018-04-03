#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <cmath>
#include "Point.hpp"

enum Direction { left, right, up, down };

bool compare(Point<int>, Point<int>);                // Return true if both points are the same
double distance(Point<int>, Point<int>);             // Euclidean distance
Direction rand(const int&, const int&);              // Returns random number b/w the given
Direction rand(const Direction&, const Direction&);  // Return random direction of the 2
bool rand_3_by_4();                                  // To lie or not to lie
Direction opposite(const Direction&);                // Return the opposite of the given direction

#endif /* HELPERS_HPP */
