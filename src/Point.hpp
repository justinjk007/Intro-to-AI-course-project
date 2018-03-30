#ifndef POINT_HPP
#define POINT_HPP

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
    T addX(int num)
    {
        return this->X + num;
    }
    T addY(int num)
    {
        return this->Y + num;
    }
};

#endif /* POINT_HPP */
