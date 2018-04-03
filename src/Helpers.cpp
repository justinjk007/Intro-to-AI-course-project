#include "Helpers.hpp"

bool compare(Point<int> lhs, Point<int> rhs)
{
    /**
     * Return true of both points are equal
     */
    return (lhs.x() == rhs.x() && lhs.y() == rhs.y());
}

double distance(Point<int> a, Point<int> b)
{
    /**
     * Return the euclidean distance between the points
     */
    double diff_x = pow(b.x() - a.x(), 2);
    double diff_y = pow(b.y() - a.y(), 2);
    return sqrt(diff_y + diff_x);
}

Direction rand(const int& floor, const int& ceiling)
{
    /**
     * Return a random direction
     */
    int val = floor + std::rand() / (RAND_MAX / ceiling + floor);
    switch (val) {
        case 1:
            return right;
        case 2:
            return left;
        case 3:
            return up;
        default:
            return down;
    }
}

Direction rand(const Direction& a, const Direction& b)
{
    /**
     * Return a random direction of the two given ones
     */
    int val = 1 + std::rand() / (RAND_MAX / 2 + 1);
    if (val == 1)
        return a;
    else
        return b;
}

bool rand_3_by_4()
{
    /**
     * This will return true 3/4 time
     */
    int val = 1 + std::rand() / (RAND_MAX / 4 + 1);
    if (val == 2)
        return true;
    else
        return false;
}

Direction opposite(const Direction& direction)
{
    /**
     * Returns the opposite direction of the given one
     */
    switch (direction) {
        case left:
            return right;
        case right:
            return left;
        case down:
            return up;
        default:
            return down;
    }
}
