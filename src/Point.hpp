#ifndef POINT_HPP
#define POINT_HPP

#include <ostream>

template <typename T>
class Point
{
   private:
    T X;
    T Y;

   public:
    Point() : X(0), Y(0) {}
    Point(T x_cord, T y_cord) : X(x_cord), Y(y_cord) {}
    T x()
    {
        return this->X;
    }
    T y()
    {
        return this->Y;
    }
    void addX(int num)
    {
        this->X += num;
    }
    void addY(int num)
    {
        this->Y += num;
    }
    friend std::ostream& operator<<(std::ostream& os, Point& p)
    {
        os << p.x() << ", " << p.y();
        return os;
    }
};

#endif /* POINT_HPP */
